#include "division.h"
#include <stdio.h>
#include <string.h>

int podziel(uint** a, uint** b, uint* rozmiar_a, uint* rozmiar_b)
{
	if (*rozmiar_b == 1 && (*b)[0] == 0)
	{
		printf("blad: dzielenie przez zero!");
		exit(EXIT_FAILURE);
	}

	//alokacja pamieci pomocniczej
	uint* iloraz = zaalokuj_pamiec_uint(sizeof(uint) * (*rozmiar_a));
	memset(iloraz, 0, sizeof(uint) * (*rozmiar_a));
	uint* reszta = zaalokuj_pamiec_uint(sizeof(uint));
	reszta[0] = 0;
	uint* rozmiar_ilorazu = zaalokuj_pamiec_uint(sizeof(uint));
	uint* rozmiar_reszty = zaalokuj_pamiec_uint(sizeof(uint));
	*rozmiar_ilorazu = *rozmiar_a;
	*rozmiar_reszty = 1;
	uint potega_liczby_2 = 1 << 31;


	for (int i = *rozmiar_a * 32 - 1; i >= 0; i--)
	{
		if ((i + 1) % 32 == 0) potega_liczby_2 = 1 << 31;
		pomnoz_przez_potege_2(&reszta, 1, rozmiar_reszty);
		if (((*a)[i / 32] & potega_liczby_2) != 0)
			reszta[0]++;
		if (wiekszy_rowny(reszta, *b, *rozmiar_reszty, *rozmiar_b) != 0)
		{
			odejmij_cale_liczby(&reszta, b, rozmiar_reszty, rozmiar_b);
			iloraz[i / 32] ^= potega_liczby_2;
		}

		potega_liczby_2 >>= 1;
	}
	

	dopasuj_pamiec(&iloraz, rozmiar_a);


	zwolnij_pamiec_uint(&reszta);
	zwolnij_pamiec_uint(&rozmiar_reszty);
	zwolnij_pamiec_uint(&rozmiar_ilorazu);

	zwolnij_pamiec_uint(a);
	*a = iloraz;
}

//int divide_and_return_remainder(uint* a, uint* b, uint* a_size, uint* b_size)
//{
//	uint* quotient = (uint*)malloc(sizeof(uint) * (*a_size));
//	memset(quotient, 0, sizeof(uint) * (*a_size));
//	uint* remainder = (uint*)malloc(sizeof(uint));
//	remainder[0] = 0;
//	uint* quotient_size = (uint*)malloc(sizeof(uint));
//	uint* remainder_size = (uint*)malloc(sizeof(uint));
//	*quotient_size = *a_size;
//	*remainder_size = 1;
//	uint power_two = 1 << 31;
//
//
//
//	for (int i = *a_size * 32 - 1; i >= 0; i--)
//	{
//		if ((i + 1) % 32 == 0) power_two = 1 << 31;
//		remainder = pomnoz_przez_potege_2(remainder, 1, remainder_size);
//		if ((a[i / 32] & power_two) != 0)
//			remainder[0]++;
//		if (greater_equal(remainder, b, *remainder_size, *b_size) != 0)
//		{
//			remainder = odejmij_cale_liczby(remainder, b, remainder_size, b_size);
//			quotient[i / 32] ^= power_two;
//		}
//
//		power_two >>= 1;
//	}
//
//
//
//	for (int i = *a_size - 1; i > 0; i--)
//		if (quotient[i] == 0)
//			(*a_size)--;
//	
//
//	for (int i = *a_size - 1; i >= 0; i--)
//		a[i] = quotient[i];
//
//	return *remainder;
//}
