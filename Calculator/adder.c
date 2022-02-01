#include "adder.h"
#include <stdlib.h>


uint dodaj_uint(uint a, uint b, unsigned char* flaga_przeniesienia)
{
	// moze dojsc do przepelnienia
	unsigned long long suma = (unsigned long long)(a) + (unsigned long long)(b) + (unsigned long long)(*flaga_przeniesienia);
	if (suma > UINT_MAX) *flaga_przeniesienia = 1;
	else *flaga_przeniesienia = 0;
	return suma;
}


void dodaj_cale_liczby(uint** a, uint** b, uint* rozmiar_a, uint* rozmiar_b)
{
	// chcemy, aby a > b
	if (*rozmiar_b > *rozmiar_a)
	{
		uint* pamiec = *a;
		*a = *b;
		*b = pamiec;
		uint rozmiar = *rozmiar_a;
		*rozmiar_a = *rozmiar_b;
		*rozmiar_b = rozmiar;
	}
	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	// dodawanie
	for (uint i = 0; i < *rozmiar_a; i++)
		(*a)[i] = dodaj_uint((i < *rozmiar_a) ? (*a)[i] : 0, (i < *rozmiar_b) ? (*b)[i] : 0, flaga_przeniesienia);
	
	// obs�uga przepelnienia
	if (*flaga_przeniesienia)
	{
		rozszerz_pamiec(a, rozmiar_a, 1);
		(*a)[*rozmiar_a - 1] = 1;
	}

	zwolnij_pamiec_uchar(&flaga_przeniesienia);
}


void dodaj_uint_do_calej_liczby(uint** a, uint b, uint* rozmiar_a)
{
	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	// dodawanie
	(*a)[0] = dodaj_uint((*a)[0], b, flaga_przeniesienia);
	int i = 1;

	// obsluga przepelnienia
	for (i; i < *rozmiar_a; i++)
	{
		if (*flaga_przeniesienia == 0) break;
		(*a)[i] = dodaj_uint((*a)[i], 0, flaga_przeniesienia);
	}


	if (i == *rozmiar_a && (*flaga_przeniesienia) != 0)
	{
		rozszerz_pamiec(a, rozmiar_a, 1);
		(*a)[*rozmiar_a - 1] = 1;
	}

	zwolnij_pamiec_uchar(&flaga_przeniesienia);
}


uint odejmij_uint(uint a, uint b, unsigned char* pozyczka)
{
	long long wynik = (long long)(a) - (long long)(b) - *pozyczka;
	*pozyczka = 0;
	while (wynik < 0)
	{
		wynik += (long long)(1) << 32;
		*pozyczka += 1;
	}
	return wynik;
}


void odejmij_cale_liczby(uint** a, uint** b, uint* rozmiar_a, uint* rozmiar_b)
{
	unsigned char* pozyczka = zaalokuj_pamiec_char(sizeof(unsigned char));
	*pozyczka = 0;


	int i = 0;
	for (i; i < *rozmiar_b; i++)
		(*a)[i] = odejmij_uint((*a)[i], (*b)[i], pozyczka);
	
	// odejmowanie
	while (i < *rozmiar_a && *pozyczka > 0)
	{
		(*a)[i] = odejmij_uint((*a)[i], 0, pozyczka);
		i++;
	}

	// zmniejszanie rozmiaru wyniku (jezeli jest taka potrzeba)
	for (int i = *rozmiar_a - 1; i > 0; i--)
	{
		if ((*a)[i] != 0) break;
		(*rozmiar_a)--;
	}

	zwolnij_pamiec_uchar(&pozyczka);
}
