void example(bool x, bool y)
{
	if(x) // these two if statements can be
	{
		if(y) // combined to if (x && y)
		{
			foo();
		}
	}
}
