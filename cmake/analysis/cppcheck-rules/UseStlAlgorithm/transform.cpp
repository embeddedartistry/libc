void f1(int* a, int* b, int n)
{
	for(int i = 0; i < n; i++)
		a[i] = g(b[i]);
}

void f2(int* a, int* b, int n)
{
	for(int i = 0; i < n; i++)
		a[i] = ns::g(b[i]);
}

void f3(int* a, int* b, int* c, int n)
{
	for(int i = 0; i < n; i++)
		a[i] = g(b[i], c[i]);
}
