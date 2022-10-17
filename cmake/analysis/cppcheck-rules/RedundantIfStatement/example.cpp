bool example(int a, int b)
{
	if(a == b) // this if statement is redundant
	{
		return true;
	}
	else
	{
		return false;
	} // the entire method can be simplified to return a == b;
}
