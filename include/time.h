#ifndef _TIME_H_
#define _TIME_H_

#include <_types/_time_t.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Types and Definitions -

#define CLOCKS_PER_SEC 1000000L

#define TIME_UTC 1

#if defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
#define __tm_gmtoff tm_gmtoff
#define __tm_zone tm_zone
#endif

typedef int clockid_t;
typedef void* timer_t;
typedef unsigned long clock_t;
typedef unsigned useconds_t;

#define _STRUCT_TIMESPEC
struct timespec
{
	time_t tv_sec;
	long tv_nsec;
};

#define _STRUCT_TIMEVAL
struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};

#define __timespec_defined 1
#define __timeval_defined 1
#define __clock_t_defined 1
#define __useconds_t_defined 1

struct tm
{
	int tm_sec; /* seconds after the minute [0-60] */
	int tm_min; /* minutes after the hour [0-59] */
	int tm_hour; /* hours since midnight [0-23] */
	int tm_mday; /* day of the month [1-31] */
	int tm_mon; /* months since January [0-11] */
	int tm_year; /* years since 1900 */
	int tm_wday; /* days since Sunday [0-6] */
	int tm_yday; /* days since January 1 [0-365] */
	int tm_isdst; /* Daylight Savings Time flag */
	long __tm_gmtoff; /* offset from CUT in seconds */
	char* __tm_zone; /* timezone abbreviation */
};

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
	defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID 3
#define CLOCK_MONOTONIC_RAW 4
#define CLOCK_REALTIME_COARSE 5
#define CLOCK_MONOTONIC_COARSE 6
#define CLOCK_BOOTTIME 7
#define CLOCK_REALTIME_ALARM 8
#define CLOCK_BOOTTIME_ALARM 9
#define CLOCK_SGI_CYCLE 10
#define CLOCK_TAI 11

#define TIMER_ABSTIME 1

struct itimerspec
{
	struct timespec it_interval;
	struct timespec it_value;
};

#endif

#pragma mark - Functions -

char* asctime(const struct tm*);

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
clock_t clock(void);
time_t time(time_t*);
double difftime(time_t, time_t);
time_t mktime(struct tm*);
size_t strftime(char* __restrict, size_t, const char* __restrict, const struct tm* __restrict);
struct tm* gmtime(const time_t*);
struct tm* localtime(const time_t*);

char* ctime(const time_t*);

int timespec_get(struct timespec*, int);
#endif

#if defined(_GNU_SOURCE) || defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || \
	defined(_BSD_SOURCE)
char* asctime_r(const struct tm* __restrict, char* __restrict);

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
struct tm* gmtime_r(const time_t* __restrict, struct tm* __restrict);
struct tm* localtime_r(const time_t* __restrict, struct tm* __restrict);
char* ctime_r(const time_t*, char*);

int nanosleep(const struct timespec*, struct timespec*);
int clock_getres(clockid_t, struct timespec*);
int clock_gettime(clockid_t, struct timespec*);
int clock_settime(clockid_t, const struct timespec*);
int clock_nanosleep(clockid_t, int, const struct timespec*, struct timespec*);
// int clock_getcpuclockid(pid_t, clockid_t*);

struct sigevent;
int timer_create(clockid_t, struct sigevent* __restrict, timer_t* __restrict);
int timer_delete(timer_t);
int timer_settime(timer_t, int, const struct itimerspec* __restrict, struct itimerspec* __restrict);
int timer_gettime(timer_t, struct itimerspec*);
int timer_getoverrun(timer_t);

extern char* tzname[2];
#endif // DISABLE_UNIMPLEMENTED_LIBC_APIS
#endif

#if defined(_XOPEN_SOURCE) || defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
char* strptime(const char* __restrict, const char* __restrict, struct tm* __restrict);
extern int daylight;
extern long timezone;
extern int getdate_err;
struct tm* getdate(const char*);
#endif // DISABLE_UNIMPLEMENTED_LIBC_APIS
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
int stime(const time_t*);
time_t timegm(struct tm*);
#endif // DISABLE_UNIMPLEMENTED_LIBC_APIS
#endif

#ifdef __cplusplus
}
#endif

#endif /* !_TIME_H_ */
