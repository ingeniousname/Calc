#include "compare.h"

char less(unsigned int* a, unsigned int* b, unsigned int a_size, unsigned int b_size) // a < b?
{
	if (a_size > b_size) return 0;
	else if (a_size < b_size) return 1;
	else
	{
		for (int i = a_size - 1; i >= 0; i--)
		{
			if (a[i] > b[i]) return 0;
			else if (a[i] < b[i]) return 1;
		}
	}
	return 0;
}

char less_equal(unsigned int* a, unsigned int* b, unsigned int a_size, unsigned int b_size) //a <= b
{
	if (a_size > b_size) return 0;
	else if (a_size < b_size) return 1;
	else
	{
		for (int i = a_size - 1; i >= 0; i--)
		{
			if (a[i] > b[i]) return 0;
			else if (a[i] < b[i]) return 1;
		}
	}
	return 1;
}

char greater(unsigned int* a, unsigned int* b, unsigned int a_size, unsigned int b_size) // a > b?
{
	if (a_size > b_size) return 1;
	else if (a_size < b_size) return 0;
	else
	{
		for (int i = a_size - 1; i >= 0; i--)
		{
			if (a[i] > b[i]) return 1;
			else if (a[i] < b[i]) return 0;
		}
	}
	return 0;
}

char wiekszy_rowny(unsigned int* a, unsigned int* b, unsigned int rozmiar_a, unsigned int rozmiar_b) // a >= b
{
	if (rozmiar_a > rozmiar_b) return 1;
	else if (rozmiar_a < rozmiar_b) return 0;
	else
	{
		for (int i = rozmiar_a - 1; i >= 0; i--)
		{
			if (a[i] > b[i]) return 1;
			else if (a[i] < b[i]) return 0;
		}
	}
	return 1;
}
