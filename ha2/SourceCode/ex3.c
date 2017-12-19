long decode2(long x, long y, long z);

//write your answer here
long decode2(long x, long y, long z) 
{
    long result;
    y = y - z;
    x = x * y;
    result = y;
    result = result << 63;
    result = result >> 63;
    result = result ^ x;
    return result;
}
