#ifndef WINT_T_H_
#define WINT_T_H_

#ifdef __APPLE__
typedef int wint_t;
#else
typedef unsigned int wint_t;
#endif

#endif // WINT_T_H_
