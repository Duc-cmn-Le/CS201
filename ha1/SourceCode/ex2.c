/* 
 * Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 -->0x1FFFF
 * Assume int is w bits long; 1 <= n <= w; 
 */
int lower_one_mask(int n):
{
    return ~((~0) << n);
}
