__attribute__((weak)) int __cxa_atexit(void (*func)(void*), void* arg, void* dso);
int __aeabi_atexit(void* obj, void (*func)(void*), void* d);

// We forward the call to cxa_atexit
int __aeabi_atexit(void* obj, void (*func)(void*), void* d)
{
	if(__cxa_atexit)
	{
		return __cxa_atexit(func, obj, d);
	}
	else
	{
		return 0;
	}
}
