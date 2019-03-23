#ifndef __SIZE_T_H_
#define __SIZE_T_H_

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#else
typedef unsigned long size_t;
#endif

typedef long ssize_t;

#endif // __SIZE_T_H_
