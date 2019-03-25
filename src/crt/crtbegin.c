// Pulled from llvm commit review

#include "__dso_handle.h"
#include <stddef.h>

/// We don't have shared libraries, so dso_handle is just NULL
__attribute__((visibility("hidden"))) void* __dso_handle = (void*)NULL;

// TODO: check that this form is a viable alternative to zero-length-array
static long* __EH_FRAME_LIST__ __attribute__((section(".eh_frame"), aligned(sizeof(void*))));
// static long __EH_FRAME_LIST__[]
//    __attribute__((section(".eh_frame"), aligned(sizeof(void *)))) = {};

extern void __register_frame_info(const void*, void*) __attribute__((weak));
extern void* __deregister_frame_info(const void*) __attribute__((weak));

#ifndef CRT_HAS_INITFINI_ARRAY
typedef void (*fp)(void);

static fp __CTOR_LIST__[] __attribute__((section(".ctors"), aligned(sizeof(fp)), used)) = {(fp)-1};
extern fp __CTOR_LIST_END__[];
#endif

static void __attribute__((used)) __do_init()
{
	static _Bool __initialized;
	if(__builtin_expect(__initialized, 0))
	{
		return;
	}
	__initialized = 1;

	static struct
	{
		void* p[8];
	} __object;
	if(__register_frame_info)
	{
		__register_frame_info(__EH_FRAME_LIST__, &__object);
	}

#ifndef CRT_HAS_INITFINI_ARRAY
	const size_t n = (size_t)__CTOR_LIST_END__ - (size_t)__CTOR_LIST__ - (size_t)1;
	for(size_t i = n; i >= 1; i--)
	{
		__CTOR_LIST__[i]();
	}
#endif
}

#ifdef CRT_HAS_INITFINI_ARRAY
__attribute__((section(".init_array"), used)) static void (*__init)(void) = __do_init;
#else // CRT_HAS_INITFINI_ARRAY
#if defined(__i386__) || defined(__x86_64__)
__asm__(".pushsection .init,\"ax\",@progbits\n\t"
		"call " __USER_LABEL_PREFIX__ "__do_init\n\t"
		".popsection");
#elif defined(__arm__)
__asm__(".pushsection .init,\"ax\",%progbits\n\t"
		"bl " __USER_LABEL_PREFIX__ "__do_init\n\t"
		".popsection");
#endif // CRT_HAS_INITFINI_ARRAY
#endif

#ifndef CRT_HAS_INITFINI_ARRAY
static fp __DTOR_LIST__[] __attribute__((section(".dtors"), aligned(sizeof(fp)), used)) = {(fp)-1};
extern fp __DTOR_LIST_END__[];
#endif

static void __attribute__((used)) __do_fini()
{
	static _Bool __finalized;
	if(__builtin_expect(__finalized, 0))
	{
		return;
	}
	__finalized = 1;

#ifndef CRT_HAS_INITFINI_ARRAY
	if(__deregister_frame_info)
	{
		__deregister_frame_info(__EH_FRAME_LIST__);
	}

	const size_t n = (size_t)__DTOR_LIST_END__ - (size_t)__DTOR_LIST__ - (size_t)1;
	for(size_t i = 1; i < n; i++)
	{
		__DTOR_LIST__[i]();
	}
#endif
}

#ifdef CRT_HAS_INITFINI_ARRAY
__attribute__((section(".fini_array"), used)) static void (*__fini)(void) = __do_fini;
#else // CRT_HAS_INITFINI_ARRAY
#if defined(__i386__) || defined(__x86_64__)
__asm__(".pushsection .fini,\"ax\",@progbits\n\t"
		"call " __USER_LABEL_PREFIX__ "__do_fini\n\t"
		".popsection");
#elif defined(__arm__)
__asm__(".pushsection .fini,\"ax\",%progbits\n\t"
		"bl " __USER_LABEL_PREFIX__ "__do_fini\n\t"
		".popsection");
#endif
#endif // CRT_HAS_INIT_FINI_ARRAY
