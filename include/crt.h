#ifndef __CRT_H_
#define __CRT_H_

#define CRT_HAS_INITFINI_ARRAY

void CRTStartup(void);
void __libc_init_array(void);
void __libc_fini_array(void);

#endif // __CRT_H_
