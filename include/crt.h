#ifndef __CRT_H_
#define __CRT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CRT_HAS_INITFINI_ARRAY

void CRTStartup(void);
void __libc_init_array(void);
void __libc_fini_array(void);

// Define this function in your application to control the statup behavior.
// This function should, at a minimum, call CRTStartup() and then call main().
// A default (weakly-linked) implementation is provided in libc that does just that.
// You can override it with a strong definition.
int entry(void);

/** Stack Check Failure Callback
 *
 * This function shall abort the function that called it with a message that a stack overflow
 * has been deteted, and then halt the program via `exit`, `abort`, or a custom panic handler.
 *
 * This function must not return!
 *
 * This function is weakly linked. You can define your own implementation in your program
 * and it will be used instead of the library default.
 *
 * By default, this function prints an error message via `printf` and calls abort().
 *
 * @post The program is terminated.
 */
__attribute__((noreturn)) void __stack_chk_fail(void);

#ifndef DISABLE_STACK_CHK_GUARD_RUNTIME_CONFIG
/** Initialize __stack_chk_guard during boot
 *
 * This function is called during the startup process as a ((constructor)),
 * ensuring it will run before the system is configured.
 *
 * * This function is weakly linked. You can define your own implementation in your program
 * and it will be used instead of the library default.
 *
 * By default, this function sets __stack_chk_guard to the pre-defined canary value.
 * Our recommendation is to override this function on your own system to randomly generate
 * the value used for __stack_chk_guard during boot or to use a unique value tied to
 * the each hardware entity.
 *
 * @returns The value to be used for __stack_chk_guard.
 */
uintptr_t __stack_chk_guard_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // __CRT_H_
