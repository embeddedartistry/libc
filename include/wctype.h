#ifndef WCTYPE_H__
#define WCTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <_types/_wchar_t.h>
#include <_types/_wint_t.h>

typedef const int* wctrans_t;
typedef unsigned long wctype_t;

#undef WEOF
#define WEOF 0xffffffffU

#define WCTYPE_ALNUM 1
#define WCTYPE_ALPHA 2
#define WCTYPE_BLANK 3
#define WCTYPE_CNTRL 4
#define WCTYPE_DIGIT 5
#define WCTYPE_GRAPH 6
#define WCTYPE_LOWER 7
#define WCTYPE_PRINT 8
#define WCTYPE_PUNCT 9
#define WCTYPE_SPACE 10
#define WCTYPE_UPPER 11
#define WCTYPE_XDIGIT 12

int iswalnum(wint_t);
int iswalpha(wint_t);
int iswblank(wint_t);
int iswcntrl(wint_t);
int iswctype(wint_t, wctype_t);
int iswdigit(wint_t);
int iswgraph(wint_t);
int iswlower(wint_t);
int iswprint(wint_t);
int iswpunct(wint_t);
int iswspace(wint_t);
int iswupper(wint_t);
int iswxdigit(wint_t);

wint_t towctrans(wint_t, wctrans_t);
wint_t towlower(wint_t);
wint_t towupper(wint_t);
wctrans_t wctrans(const char*);
wctype_t wctype(const char*);

#ifdef __cplusplus
}
#endif

#endif // WCTYPE_H__
