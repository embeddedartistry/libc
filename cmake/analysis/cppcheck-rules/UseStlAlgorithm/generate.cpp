void f1(int* a, int* b, int n)
{
	for(int i = 0; i < n; i++)
		a[i] = gen();
}

void f2(int* a, int* b, int n)
{
	for(int i = 0; i < n; i++)
		a[i] = ns::gen();
}
