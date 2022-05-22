#include <stdio.h>

#define MAX_SIZE 100

int get_vectors_size();
void read_vector_values(int vec[], int size);
int scalar_product(int vec1[], int vec2[], int size);
void print_result(int res);

/* main - calculates the scalar product of 2 vectors */
int main()
{
	int v1[MAX_SIZE], v2[MAX_SIZE], size, result;

	size = get_vectors_size();
	read_vector_values(v1, size);
	read_vector_values(v2, size);
	result = scalar_product(v1, v2, size);
	print_result(result);

	return 0;
}

/* get vectors size from input */
int get_vectors_size()
{
	int size;
	printf("Enter the vectors size (max size is %d): ", MAX_SIZE);
	scanf("%d", &size);
	printf("%d\n", size);
	return size;
}

/* read vectors values from input */
void read_vector_values(int vec[], int size)
{
	int i;

	printf("\nEnter the %d vector values", size);
	for (i = 0; i < size; i++)
	{
		printf("\nEnter value %d: ", i + 1);
		scanf("%d", &vec[i]);
		printf("%d", vec[i]);
	}
}

/* calculate the scalar product */
int scalar_product(int vec1[], int vec2[], int size)
{
	int i, res = 0;

	for (i = 0; i < size; i++)
		res += vec1[i] * vec2[i];

	return res;
}

/* print result */
void print_result(int res)
{
	printf("\nThe scalar product is: %d\n", res);
}
