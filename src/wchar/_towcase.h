#ifndef TOWCASE_H__
#define TOWCASE_H__

#include <wctype.h>

#ifdef __cplusplus
extern "C" {
#endif

wchar_t __towcase(wchar_t wc, int lower);

#ifdef __cplusplus
}
#endif

#endif // TOWCASE_H_
