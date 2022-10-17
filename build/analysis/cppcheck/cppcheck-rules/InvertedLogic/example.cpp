int example(int a)
{
	int i;
	if(a != 0) // if (a == 0)
	{ // {
		i = 1; //      i = 0;
	} // }
	else // else
	{ // {
		i = 0; //      i = 1;
	} // }

	return !i ? -1 : 1; // return i ? 1 : -1;
}
