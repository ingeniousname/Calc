#include "division.h"
#include "Utility/pamiec.h"
#include <stdio.h>
#include <string.h>

void podziel(Number* n1, Number* n2)
{
	if (n2->size == 1 && (n2->data)[0] == 0)
	{
		printf("Dzielenie przez 0!");
		exit(EXIT_FAILURE);
	}

	//alokacja pamieci pomocniczej
	Number iloraz, reszta;
	zaalokuj(&iloraz, sizeof(uint) * (n1->size));
	zaalokuj(&reszta, sizeof(uint));
	memset(iloraz.data, 0, sizeof(uint) * (n1->size));
	iloraz.size = n1->size;
	reszta.data = 0;
	reszta.size = 1;

	
	uint potega_liczby_2 = 1 << 31;


	// prosty algorytm z przesuwaniem bitow reszty z dzielenia, az nie stanie sie ona wieksza od dzielonej liczby

	for (int i = n1->size * 32 - 1; i >= 0; i--)
	{
		if ((i + 1) % 32 == 0) potega_liczby_2 = 1 << 31;
		pomnoz_przez_potege_2(&reszta, 1);

		if (((n1->data)[i / 32] & potega_liczby_2) != 0)
			reszta.data[0]++;

		if (wiekszy_rowny(&reszta, n2) != 0)
		{
			odejmij_cale_liczby(&reszta, n2);
			iloraz.data[i / 32] ^= potega_liczby_2;
		}

		potega_liczby_2 >>= 1;
	}
	

	dopasuj(&iloraz);

	//TODO ZWOLNIC PAMIEC

	//zwolnij_pamiec_uint(&reszta);
	//zwolnij_pamiec_uint(&rozmiar_reszty);
	//zwolnij_pamiec_uint(&rozmiar_ilorazu);
//
	//zwolnij_pamiec_uint(a);
	n1->data = iloraz.data;
}

void podziel_i_zwroc_modulo(Number* n1, Number* n2)
{
	if (n2->size == 1 && (n2->data)[0] == 0)
	{
		printf("Dzielenie przez 0!");
		exit(EXIT_FAILURE);
	}

	//alokacja pamieci pomocniczej
	Number iloraz, reszta;
	zaalokuj(&iloraz, sizeof(uint) * (n1->size));
	zaalokuj(&reszta, sizeof(uint));
	memset(iloraz.data, 0, sizeof(uint) * (n1->size));
	iloraz.size = n1->size;
	reszta.data = 0;
	reszta.size = 1;

	uint potega_liczby_2 = 1 << 31;


	// prosty algorytm z przesuwaniem bitow reszty z dzielenia, az nie stanie sie ona wieksza od dzielonej liczby

	for (int i = n1->size * 32 - 1; i >= 0; i--)
	{
		if ((i + 1) % 32 == 0) potega_liczby_2 = 1 << 31;
		pomnoz_przez_potege_2(&reszta, 1);

		if (((n1->data)[i / 32] & potega_liczby_2) != 0)
			reszta.data[0]++;

		if (wiekszy_rowny(&reszta, n2) != 0)
		{
			odejmij_cale_liczby(&reszta, n2);
			iloraz.data[i / 32] ^= potega_liczby_2;
		}

		potega_liczby_2 >>= 1;
	}


	dopasuj(&reszta);
	n1->size = reszta.size;

	// TODO ZWOLNIC PAMIEC

	//zwolnij_pamiec_uint(&iloraz);
	//zwolnij_pamiec_uint(&rozmiar_reszty);
	//zwolnij_pamiec_uint(&rozmiar_ilorazu);
//
	//zwolnij_pamiec_uint(a);
	n1->data = reszta.data;
}
