#ifndef STDIO_H__
#define STDIO_H__

#include <printf.h>
#include <stdarg.h>
#include <stddef.h>
#include <wctype.h> //TODO: eliminate need for this header here (refactor types?)

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/// NOTE: The files included here are primarily stubs to get C++ compiling.
/// If you are linking on a host machine, these functions will need to be
///	 supplied by the system library
/// If you are linking on bare metal, these symbols will not be defined!
/// Only the functions defined in printf.h and in the Supported Functions
/// section below are currently safe for bare metal

#pragma mark - Definitions -

#undef EOF
#define EOF (-1)

typedef union _G_fpos64_t
{
	char __opaque[16];
	long long __lldata;
	double __align;
} fpos_t;

/*
 * Stdio buffers.
 */
struct __sbuf
{
	unsigned char* _base;
	int _size;
};

/*
 * struct __sFILE_fake is the start of a struct __sFILE, with only the
 * minimal fields allocated.  In __sinit() we really allocate the 3
 * standard streams, etc., and point away from this fake.
 */
struct __sFILE_fake
{
	unsigned char* _p; /* current position in (some) buffer */
	int _r; /* read space left for getc() */
	int _w; /* write space left for putc() */
	short _flags; /* flags, below; this FILE is free if 0 */
	short _file; /* fileno, if Unix descriptor, else -1 */
	struct __sbuf _bf; /* the buffer (at least 1 byte, if !NULL) */
	int _lbfsize; /* 0 or -_bf._size, for inline putc */

	struct _reent* _data;
};

#if !defined(__FILE_defined)
typedef struct __sFILE_fake FILE;
#define __FILE_defined
#endif

#pragma mark - Supported Functions -

/// Requires a definition of _putchar() for your platform
int putchar(int c);
int puts(const char*);

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
int asprintf(char**, const char*, ...);
int vasprintf(char**, const char*, __isoc_va_list);
#endif

#pragma mark - Unsupported Functions -

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS

int fseek(FILE*, long, int);
long ftell(FILE*);
void rewind(FILE*);

int fgetpos(FILE* __restrict, fpos_t* __restrict);
int fsetpos(FILE*, const fpos_t*);

size_t fread(void* __restrict, size_t, size_t, FILE* __restrict);
size_t fwrite(const void* __restrict, size_t, size_t, FILE* __restrict);

char* fgets(char* __restrict, int, FILE* __restrict);
#if __STDC_VERSION__ < 201112L
char* gets(char*);
#endif

int fputc(int, FILE*);
int putc(int, FILE*);

wchar_t* fgetws(wchar_t* __restrict, int, FILE* __restrict);
int fputws(const wchar_t* __restrict, FILE* __restrict);

int fgetc(FILE*);
int getc(FILE*);
int getchar(void);
int ungetc(int, FILE*);

wint_t fgetwc(FILE*);
wint_t getwc(FILE*);
wint_t getwchar(void);
wint_t ungetwc(wint_t, FILE*);

wint_t fputwc(wchar_t, FILE*);
wint_t putwc(wchar_t, FILE*);
wint_t putwchar(wchar_t);

char* tmpnam(char*);
FILE* tmpfile(void);

int fwide(FILE*, int);

int fputs(const char* __restrict, FILE* __restrict);

FILE* fopen(const char* __restrict, const char* __restrict);
FILE* freopen(const char* __restrict, const char* __restrict, FILE* __restrict);
int fclose(FILE*);

int feof(FILE*);
int ferror(FILE*);
int fflush(FILE*);
void clearerr(FILE*);

int remove(const char*);
int rename(const char*, const char*);

int setvbuf(FILE* __restrict, char* __restrict, int, size_t);
void setbuf(FILE* __restrict, char* __restrict);

int scanf(const char* __restrict, ...);
int fscanf(FILE* __restrict, const char* __restrict, ...);
int sscanf(const char* __restrict, const char* __restrict, ...);
int vscanf(const char* __restrict, __isoc_va_list);
int vfscanf(FILE* __restrict, const char* __restrict, __isoc_va_list);
int vsscanf(const char* __restrict, const char* __restrict, __isoc_va_list);
int wscanf(const wchar_t* __restrict, ...);
int fwscanf(FILE* __restrict, const wchar_t* __restrict, ...);
int swscanf(const wchar_t* __restrict, const wchar_t* __restrict, ...);
int vwscanf(const wchar_t* __restrict, __isoc_va_list);
int vfwscanf(FILE* __restrict, const wchar_t* __restrict, __isoc_va_list);
int vswscanf(const wchar_t* __restrict, const wchar_t* __restrict, __isoc_va_list);

#ifndef vprintf
// vprintf is defined in printf.h
int vprintf(const char* __restrict, __isoc_va_list);
#endif

/// Unsupported printf variants

void perror(const char*);

int wprintf(const wchar_t* __restrict, ...);
int fprintf(FILE* __restrict, const char* __restrict, ...);
int vfprintf(FILE* __restrict, const char* __restrict, __isoc_va_list);
int vsprintf(char* __restrict, const char* __restrict, __isoc_va_list);
int fwprintf(FILE* __restrict, const wchar_t* __restrict, ...);
int swprintf(wchar_t* __restrict, size_t, const wchar_t* __restrict, ...);
int vwprintf(const wchar_t* __restrict, __isoc_va_list);
int vfwprintf(FILE* __restrict, const wchar_t* __restrict, __isoc_va_list);
int vswprintf(wchar_t* __restrict, size_t, const wchar_t* __restrict, __isoc_va_list);
#endif

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // STDIO_H__
