/*
 * C expression yeild the least significant byte of x 
 * and the remaining bytes of y 
 */

(x & 0xFF) | (y & ~(0xFF))
