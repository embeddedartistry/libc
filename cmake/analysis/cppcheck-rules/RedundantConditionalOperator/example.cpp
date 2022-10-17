void example(int a, int b, int c)
{
	bool b1 = a > b ? true : false; // true/false: bool b1 = a > b;
	bool b2 = a > b ? false : true; // false/true: bool b2 = !(a > b);
	(void)b1;
	(void)b2;
}
