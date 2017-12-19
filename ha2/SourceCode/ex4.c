//Fill the missing parts
long loop(long x, long n)
{
	long result = 0;
	long mark;
	for (mark = 1; mark != 0; mark = mark << n)
	{
		result |= x & mark;
	}
	return result;
}
