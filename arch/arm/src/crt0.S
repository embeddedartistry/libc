/* Check for targets supporting only Thumb instructions (eg. ARMv6-M) or
   supporting Thumb-2 instructions, since ARM instructions may not be available */
#if __thumb2__ || (__thumb__ && !__ARM_ARCH_ISA_ARM)
# define PREFER_THUMB
#endif

/* Identify processors only capable of executing Thumb-1 instructions.  */
#if __ARM_ARCH_ISA_THUMB == 1 && (!defined(__ARM_ARCH_ISA_ARM) || \
	(defined(__ARM_ARCH_ISA_ARM) && !__ARM_ARCH_ISA_ARM))
# define THUMB1_ONLY
#endif

/* M profile architectures.  This is a different set of architectures than
   those not having ARM ISA because it does not contain ARMv7.  This macro is
   necessary to test which architectures use bkpt as semihosting interface from
   architectures using svc.  */
#if (!defined(__ARM_ARCH_ISA_ARM) || (defined(__ARM_ARCH_ISA_ARM) && !__ARM_ARCH_ISA_ARM)) \
	&& (!defined(__ARM_ARCH_7__) || (defined(__ARM_ARCH_7__) && !__ARM_ARCH_7__))
# define THUMB_VXM
#endif

/* Defined if this target supports the BLX Rm instruction.  */
#if  !defined(__ARM_ARCH_2__)   \
  && !defined(__ARM_ARCH_3__)	\
  && !defined(__ARM_ARCH_3M__)	\
  && !defined(__ARM_ARCH_4__)	\
  && !defined(__ARM_ARCH_4T__)
# define HAVE_CALL_INDIRECT
#endif

/* ANSI concatenation macros.  */
#define CONCAT(a, b) CONCAT2(a, b)
#define CONCAT2(a, b) a ## b

#ifdef __USER_LABEL_PREFIX__
#define FUNCTION( name ) CONCAT (__USER_LABEL_PREFIX__, name)
#else
#define FUNCTION( name ) CONCAT (_, name)
#endif

#if defined(__ARM_EABI__) && defined(__thumb__) && !defined(__thumb2__)
/* For Thumb1 we need to force the architecture to be sure that we get the
   correct attributes on the object file; otherwise the assembler will get
   confused and mark the object as being v6T2.  */
#if defined(__ARM_ARCH_4T__)
	.arch armv4t
#elif defined(__ARM_ARCH_5T__) || defined(__ARM_ARCH_5TE__)
	/* Nothing in this object requires higher than v5.  */
	.arch armv5t
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) \
	|| defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) \
	|| defined(__ARM_ARCH_6ZK__)
	/* Nothing in this object requires higher than v6.  */
	.arch armv6
#elif defined(__ARM_ARCH_6M__)
	.arch armv6-m
#endif
#endif

/* .text is used instead of .section .text so it works with arm-aout too.  */
	.text
	.syntax unified
#ifdef PREFER_THUMB
	.thumb
.macro FUNC_START name
	.global \name
	.thumb_func
\name:
.endm
#else
	.code 32
.macro FUNC_START name
	.global	\name
\name:
.endm
#endif

.macro indirect_call reg
#ifdef HAVE_CALL_INDIRECT
	blx \reg
#else
	mov	lr, pc
	mov	pc, \reg
#endif
.endm

	.align 	0

	FUNC_START	_start
#if defined(__ELF__) && !defined(__USING_SJLJ_EXCEPTIONS__)
	/* Annotation for EABI unwinding tables.  */
	.fnstart
#endif

/* Start by setting up a stack.  */
	/*  Set up the stack pointer to a fixed value.  */
	/*  Changes by toralf:
	    - Allow linker script to provide stack via __stack symbol - see
	      defintion of .Lstack
	    - Provide "hooks" that may be used by the application to add
	      custom init code - see .Lhwinit and .Lswinit
	    - Go through all execution modes and set up stack for each of them.
	      Loosely based on init.s from ARM/Motorola example code.
              Note: Mode switch via CPSR is not allowed once in non-privileged
		    mode, so we take care not to enter "User" to set up its sp,
		    and also skip most operations if already in that mode.  */

	ldr	r3, .Lstack
	cmp	r3, #0
#ifdef __thumb2__
	it	eq
#endif
#ifdef __ARM_ARCH_6M__
	bne	.LC28
	ldr	r3, .LC0
.LC28:
#else
	ldreq	r3, .LC0
#endif
	/* Note: This 'mov' is essential when starting in User, and ensures we
		 always get *some* sp value for the initial mode, even if we
		 have somehow missed it below (in which case it gets the same
		 value as FIQ - not ideal, but better than nothing).  */
	mov	sp, r3
#ifdef PREFER_THUMB
	/* XXX Fill in stack assignments for interrupt modes.  */
#else
	mrs	r2, CPSR
	tst	r2, #0x0F	/* Test mode bits - in User of all are 0.  */
	beq	.LC23		/* "eq" means r2 AND #0x0F is 0.  */
	msr     CPSR_c, #0xD1	/* FIRQ mode, interrupts disabled.  */
	mov 	sp, r3
	sub	sl, sp, #0x1000	/* This mode also has its own sl (see below).  */

	mov	r3, sl
	msr     CPSR_c, #0xD7	/* Abort mode, interrupts disabled.  */
	mov	sp, r3
	sub	r3, r3, #0x1000

	msr     CPSR_c, #0xDB	/* Undefined mode, interrupts disabled.  */
	mov	sp, r3
	sub	r3, r3, #0x1000

	msr     CPSR_c, #0xD2	/* IRQ mode, interrupts disabled.  */
	mov	sp, r3
	sub	r3, r3, #0x2000

	msr     CPSR_c, #0xD3	/* Supervisory mode, interrupts disabled.  */

	mov	sp, r3
	sub	r3, r3, #0x8000	/* Min size 32k.  */
	bic	r3, r3, #0x00FF	/* Align with current 64k block.  */
	bic	r3, r3, #0xFF00

	str	r3, [r3, #-4]	/* Move value into user mode sp without */
	ldmdb	r3, {sp}^       /* changing modes, via '^' form of ldm.  */
	orr	r2, r2, #0xC0	/* Back to original mode, presumably SVC, */
	msr	CPSR_c, r2	/* with FIQ/IRQ disable bits forced to 1.  */
#endif
.LC23:
	/* Setup a default stack-limit in-case the code has been
	   compiled with "-mapcs-stack-check".  Hard-wiring this value
	   is not ideal, since there is currently no support for
	   checking that the heap and stack have not collided, or that
	   this default 64k is enough for the program being executed.
	   However, it ensures that this simple crt0 world will not
	   immediately cause an overflow event:  */
#ifdef __ARM_ARCH_6M__
	movs	r2, #64
	lsls	r2, r2, #10
	subs	r2, r3, r2
	mov	sl, r2
#else
	sub	sl, r3, #64 << 10	/* Still assumes 256bytes below sl.  */
#endif

#ifdef CRT0_INITIALIZES_BSS__
	/* Zero the memory in the .bss section.  */
	movs 	a2, #0			/* Second arg: fill value.  */
	mov	fp, a2			/* Null frame pointer.  */
	mov	r7, a2			/* Null frame pointer for Thumb.  */

	ldr	a1, .LC1		/* First arg: start of memory block.  */
	ldr	a3, .LC2
	subs	a3, a3, a1		/* Third arg: length of block.  */


#if __thumb__ && !defined(PREFER_THUMB)
	/* Enter Thumb mode...  */
	add	a4, pc, #1	/* Get the address of the Thumb block.  */
	bx	a4		/* Go there and start Thumb decoding.  */

	.code 16
	.global __change_mode
	.thumb_func
__change_mode:
#endif

	bl	FUNCTION (memset)
#endif // CRT0_INITIALIZES_BSS__

.LC25:
	movs	r0, #0		/* No arguments.  */
	movs	r1, #0		/* No argv either.  */

	// Our framework jumps to entry, which boots the system.
	// Jumping to main would skip CRT startup and system initialization
	// A default weak implementation is supplied by libc which handles these
	// two actions.
	bl	FUNCTION (entry)

	// We allow exit to be weakly defined, since we might be compiling without exit support
	ldr	r3, .Lexit
	cmp	r3, #0
	beq	.Done
	indirect_call r3

.Done:
#if __thumb__ && !defined(PREFER_THUMB)
	/* Come out of Thumb mode.  This code should be redundant.  */
	mov	a4, pc
	bx	a4

	.code 32
	.global change_back
change_back:
	/* Halt the execution.  This code should never be executed.  */
	/* With no debug monitor, this probably aborts (eventually).
	   With a Demon debug monitor, this halts cleanly.
	   With an Angel debug monitor, this will report 'Unknown SWI'.	 */
	swi	SWI_Exit
#endif

	/* For Thumb, constants must be after the code since only
	   positive offsets are supported for PC relative addresses.  */
	.align 0
.LC0:

	/* Changes by toralf: Provide alternative "stack" variable whose value
	   may be defined externally; .Lstack will be used instead of .LC0 if
	   it points to a non-0 value. Also set up references to "hooks" that
           may be used by the application to provide additional init code.  */
#ifdef __pe__
	.word	0x800000
#else
	.word	0x80000			/* Top of RAM on the PIE board.  */
#endif

.Lstack:
	.word	__stack

.Lexit:
	.word FUNCTION (exit)

	/* Set up defaults for the above variables in the form of weak symbols
	   - so that application will link correctly, and get value 0 in
	   runtime (meaning "ignore setting") for the variables, when the user
	   does not provide the symbols. (The linker uses a weak symbol if,
	   and only if, a normal version of the same symbol isnt provided
	   e.g. by a linker script or another object file).  */

	.weak __stack
	.weak FUNCTION (exit)

#if defined(__ELF__) && !defined(__USING_SJLJ_EXCEPTIONS__)
	/* Protect against unhandled exceptions.  */
	.cantunwind
	.fnend
#endif
#ifdef CRT0_INITIALIZES_BSS__
.LC1:
	.word	__bss_start__
.LC2:
	.word	__bss_end__
#endif

#ifdef __pe__
	.section .idata$3
	.long	0,0,0,0,0,0,0,0
#endif
