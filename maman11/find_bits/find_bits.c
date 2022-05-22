#include <stdio.h>

/* number of bits in unsigned long */
#define BITS_NUMBER 32

unsigned long get_value();
int find_bits(unsigned long x, unsigned long y);
void print_result(int res);

/* main - find the sum of the common 'on' bits between 2 numbers */
int main()
{
	unsigned long x, y;
	int res;

	x = get_value();
	y = get_value();
	res = find_bits(x, y);
	print_result(res);

	return 0;
}

/* get a value from input */
unsigned long get_value()
{
	unsigned long val;
	printf("Enter a value: \n");
	scanf("%lu", &val);
	printf("%lu\n", val);
	return val;
}

/* finds the sum of the common 1 bits between 2 numbers */
int find_bits(unsigned long x, unsigned long y)
{
	int bitsCount = 0, i = 0;
	unsigned long xShifted = x, yShifted = y;

	/* shift each number to the right, 1 bit at a time, until no more 1 bits */
	for (i = 0; i < BITS_NUMBER && xShifted > 0; i++)
	{
		xShifted = x >> i;
		yShifted = y >> i;

		/* check if the last digit of each number is 1 */
		if ((xShifted & 1) & (yShifted & 1))
			bitsCount++;
	}

	return bitsCount;
}

/* print the result to output */
void print_result(int res)
{
	printf("Number of common 1 bits: %d\n", res);
}
