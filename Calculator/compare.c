#include "compare.h"

char less(Number* n1, Number* n2) // a < b?
{
	if (n1->size > n2->size) return 0;
	else if (n1->size < n2->size) return 1;
	else
	{
		for (int i = n1->size - 1; i >= 0; i--)
		{
			if (n1->data[i] > n2->data[i]) return 0;
			else if (n1->data[i] < n2->data[i]) return 1;
		}
	}
	return 0;
}

char less_equal(Number* n1, Number* n2) //a <= b
{
	if (n1->size > n2->size) return 0;
	else if (n1->size < n2->size) return 1;
	else
	{
		for (int i = n1->size - 1; i >= 0; i--)
		{
			if (n1->data[i] > n2->data[i]) return 0;
			else if (n1->data[i] < n2->data[i]) return 1;
		}
	}
	return 1;
}

char greater(Number* n1, Number* n2) // a > b?
{
	if (n1->size > n2->size) return 1;
	else if (n1->size < n2->size) return 0;
	else
	{
		for (int i = n1->size - 1; i >= 0; i--)
		{
			if (n1->data[i] > n2->data[i]) return 1;
			else if (n1->data[i] < n2->data[i]) return 0;
		}
	}
	return 0;
}

char wiekszy_rowny(Number* n1, Number* n2) // a >= b
{
	if (n1->size  > n2->size) return 1;
	else if (n1->size < n2->size) return 0;
	else
	{
		for (int i = n1->size - 1; i >= 0; i--)
		{
			if (n1->data[i] > n2->data[i]) return 1;
			else if (n1->data[i] < n2->data[i]) return 0;
		}
	}
	return 1;
}
