#ifndef __SETJMP_H_
#define __SETJMP_H_

#include <_types/_setjmp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __jmp_buf_tag
{
	__jmp_buf __jb;
	unsigned long __fl;
	unsigned long __ss[128 / sizeof(long)];
} jmp_buf[1];

typedef jmp_buf sigjmp_buf;

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
int sigsetjmp(sigjmp_buf, int);
void siglongjmp(sigjmp_buf, int) __attribute__((noreturn));
#endif

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
int _setjmp(jmp_buf);
int setjmp(jmp_buf);

void _longjmp(jmp_buf, int) __attribute__((noreturn));
void longjmp(jmp_buf, int) __attribute__((noreturn));
#endif

#ifdef __cplusplus
}
#endif

#endif // __SETJMP_H_
