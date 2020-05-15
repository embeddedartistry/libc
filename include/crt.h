#ifndef __CRT_H_
#define __CRT_H_

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

#endif // __CRT_H_
