typedef struct
{
	int x[A][B]; /* Unknown constants A and B */
	long y;
}str1;

typedef struct
{
	char array[B];
	int t;
	short s[A];
	long u;
}str2;

void setVal(str1 *p, str2 *q)
{
	long v1 = q->t;
	long v2 = q->u;
	p->y = v1 + v2;
}