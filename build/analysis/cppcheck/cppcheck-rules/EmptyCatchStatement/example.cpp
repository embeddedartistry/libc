void example()
{
	try
	{
		int* m = new int[1000];
	}
	catch(...) // empty catch statement, this swallows an exception
	{
	}
}
