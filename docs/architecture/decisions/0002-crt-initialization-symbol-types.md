# 2. CRT Initialization Symbol Types

Date: 2020-10-15

## Status

Accepted

## Context

We found a bug in the `__libc_init_array()` and `__libc_fini_array()` functions - we were doing math on uintptr_t, which generated 4x or 8x the number of entries as was actually present. This might result in no noticeable issue, or it might crash your system - depends on what functions get called in the bonus round!

When implementing the tests, we had trouble with the form of `* []` (array of function pointers), so we changed the types to `**`. This gave us the behavior we wanted, enabling the testing to check the logic for these functions on macOS.

```
extern void (**__preinit_array_start)(void) __attribute__((weak));
extern void (**__preinit_array_end)(void) __attribute__((weak));
extern void (**__init_array_start)(void) __attribute__((weak));
extern void (**__init_array_end)(void) __attribute__((weak));
extern void (**__fini_array_start)(void) __attribute__((weak));
extern void (**__fini_array_end)(void) __attribute__((weak));

// Currently these tests only run on MacOS
__attribute__((section("__DATA,.preinit_array"))) void (**__preinit_array_start)(void) = preinit_call_list;
__attribute__((section("__DATA,.preinit_array"))) void (**__preinit_array_end)(void) = &preinit_call_list[1];
__attribute__((section("__DATA,.init_array"))) void (**__init_array_start)(void) = init_call_list;
__attribute__((section("__DATA,.init_array"))) void (**__init_array_end)(void) = &init_call_list[2];
__attribute__((section("__DATA,.fini_array")))void (**__fini_array_start)(void)  = fini_call_list;
__attribute__((section("__DATA,.fini_array")))void (**__fini_array_end)(void) = &fini_call_list[3];
```

Example output:

```
[0/1] Running all tests.
1/3 printf_tests      OK             0.34s
2/3 libc_tests        OK             0.55s
3/3 stackprotect_test EXPECTEDFAIL   0.01s


Ok:                 2
Expected Fail:      1
Fail:               0
Unexpected Pass:    0
Skipped:            0
Timeout:            0

preinit array: 00000001029600C0, end: 00000001029600C0
init array: 0000000102960080, end: 0000000102960080
fini array: 00000001029600A0, end: 00000001029600B8
Count: 0, preinit_array_end: 00000001029600C0, preinit_array_start: 00000001029600C0, CTR_TO_PTR_ADJUST: 3, count calculated: 0
```

Using a `**` works on macOS when testing, but does not work on device - we need to adjust our logic in that case to take the address of the symbols (e.g., `&__preinit_array_end`). 

```
(gdb) n
52        count = (size_t)(((uintptr_t)__init_array_end - (uintptr_t)__init_array_start) >>
(gdb) n
54        for(size_t i = 0; i < count; i++)
(gdb) p count
$2 = 100662561
(gdb) p __init_array_end
$3 = (void (**)(void)) 0x200001ec <__cxa_unexpected_handler>
(gdb) p __init_array_start
$4 = (void (**)(void)) 0x8000d65
     <_GLOBAL__sub_I_cxa_default_handlers.cpp(void)>
(gdb) p &__init_array_start
$5 = (void (***)(void)) 0x20000044
(gdb) p &__init_array_end
$6 = (void (***)(void)) 0x20000048
(gdb) p __init_array_start[0]
$7 = (void (*)(void)) 0xfff64fb5
(gdb) p __preinit_array_start
$9 = (void (**)(void)) 0x8000d65 <_GLOBAL__sub_I_cxa_default_handlers.cpp(void)>
(gdb) p &__preinit_array_start
$10 = (void (***)(void)) 0x20000044
```

However, taking the address of these symbols makes the test fail again!

```
<testsuites>
  <testsuite name="crt_tests" time="0.000" tests="2" failures="2" errors="0" skipped="0" >
    <testcase name="check_crt_init_routines" time="0.000" >
      <failure><![CDATA[0x1 != 0x2
../test/crt/crt_init_array.c:80: error: Failure!]]></failure>
    </testcase>
    <testcase name="check_crt_fini_routines" time="0.000" >
      <failure><![CDATA[0x1 != 0x3
../test/crt/crt_init_array.c:88: error: Failure!]]></failure>
    </testcase>
  </testsuite>
```

## Decision

Not knowing whether this is a Clang or MacOS specific behavior, we'll just use an `#ifdef` to select the proper form when testing. This will ensure that current devices work as-is, and our testing form is only used when building libc tests on macOS. If this changes (e.g., we find out it's actually predicated on `__APPLE__`), we can adjust as-is.

```
#ifdef ENABLE_CRT_TESTING
// Note that this might actually be #if __APPLE__, but we only
// Use this file on MacOS for testing purposes.
extern void (**__preinit_array_start)(void) __attribute__((weak));
extern void (**__preinit_array_end)(void) __attribute__((weak));
extern void (**__init_array_start)(void) __attribute__((weak));
extern void (**__init_array_end)(void) __attribute__((weak));
extern void (**__fini_array_start)(void) __attribute__((weak));
extern void (**__fini_array_end)(void) __attribute__((weak));
#else
extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));
extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));
#endif
```

## Consequences

There is still the possibility of incorrect behavior with other compilers/systems.
