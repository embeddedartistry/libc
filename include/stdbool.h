#ifndef __STDBOOL_H_
#define __STDBOOL_H_

#ifndef __cplusplus

/*
 * Only defined for C, since C++ has its own bool support
 * */

/** Expands to the integer constant 1. */
#define true 1

/** Expands to the integer constant 0. */
#define false 0

/** Expands to _Bool. */
typedef _Bool bool;

#endif

#endif //__STDBOOL_H_
