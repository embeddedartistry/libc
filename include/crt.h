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

#endif // __CRT_H_
