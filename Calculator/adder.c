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


void dodaj_cale_liczby(Number* n1, Number* n2)
{
	// chcemy, aby a > b
	if (n2->size > n1->size)
	{
		unsigned* temp = n1->data;
		unsigned sizetemp = n1->size;
		n1->data = n2->data;
		n1->size = n2->size;
		n2->data = temp;
		n2->size = sizetemp;
	}
	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	// dodawanie
	for (uint i = 0; i < n1->size; i++)
		(n1->data)[i] = dodaj_uint((i < n1->size) ? (n1->data)[i] : 0, (i < n2->size) ? (n2->data)[i] : 0, flaga_przeniesienia);
	
	// obs�uga przepelnienia
	if (*flaga_przeniesienia)
	{
		rozszerz(n1, 1);
		(n1->data)[n1->size - 1] = 1;
	}

	zwolnij_pamiec_uchar(&flaga_przeniesienia);
}


void dodaj_uint_do_calej_liczby(Number* N,  uint b)
{
	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	// dodawanie
	(N->data)[0] = dodaj_uint((N->data)[0], b, flaga_przeniesienia);
	int i = 1;

	// obsluga przepelnienia
	for (i; i < N->size; i++)
	{
		if (*flaga_przeniesienia == 0) break;
		(N->data)[i] = dodaj_uint((N->data)[i], 0, flaga_przeniesienia);
	}


	if (i == N->size && (*flaga_przeniesienia) != 0)
	{
		rozszerz(N, 1);
		(N->data)[N->size - 1] = 1;
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


void odejmij_cale_liczby(Number* n1, Number* n2)
{
	unsigned char* pozyczka = zaalokuj_pamiec_char(sizeof(unsigned char));
	*pozyczka = 0;


	int i = 0;
	for (i; i < n2->size; i++)
		(n1->data)[i] = odejmij_uint((n1->data)[i], (n2->data)[i], pozyczka);
	
	// odejmowanie
	while (i < n1->size && *pozyczka > 0)
	{
		(n1->data)[i] = odejmij_uint((n1->data)[i], 0, pozyczka);
		i++;
	}

	// zmniejszanie rozmiaru wyniku (jezeli jest taka potrzeba)
	for (int i = n1->size - 1; i > 0; i--)
	{
		if ((n1->data)[i] != 0) break;
		(n1->size)--;
	}

	zwolnij_pamiec_uchar(&pozyczka);
}
