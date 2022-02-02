#include "multiplier.h"
#include "Utility/pamiec.h"
#include <string.h>
#include <stdio.h>

void pomnoz_cala_liczbe_przez_uint(Number* N, uint b)
{
	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	// uzywamy formatu unsigned long long - nie dojdzie do przepelnienia
	unsigned long long pojedynczy_wynik = (unsigned long long) ((N->data)[0]) * (unsigned long long) (b);


	//alokacja pamieci na caly wynik 
	rozszerz(N, sizeof(uint));
	(N->data)[N->size - 1] = 0;
	(N->data)[0] = 0;

	
	// "szkolny" algorytm mnozenia (jak na kartce)
	for (uint i = 0; i < N->size - 1; i++)
	{
		uint pamiec = (N->data)[i + 1];
		(N->data)[i] = dodaj_uint((N->data)[i], (uint)pojedynczy_wynik, flaga_przeniesienia);
		(N->data)[i + 1] = dodaj_uint(0, (uint)(pojedynczy_wynik >> 32), flaga_przeniesienia);

		pojedynczy_wynik = (unsigned long long) (pamiec) * (unsigned long long) (b);
		if (*flaga_przeniesienia != 0)
		{
			pojedynczy_wynik += ((unsigned long long)(1) << 32);
			*flaga_przeniesienia = 0;
		}
	}

	// zmniejszanie rozmiaru wyniku (jezeli jest taka potrzeba)
	zwolnij_pamiec_uchar(&flaga_przeniesienia);
	dopasuj(N);
}

void pomnoz_cale_liczby(Number* n1, Number* n2)
{
	// alokacja pamieci na iloczyn
	uint* wynik = zaalokuj_pamiec_uint(sizeof(uint) * (n1->size + n2->size));
	memset(wynik, 0, sizeof(uint) * (n1->size + n2->size));

	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	//"szkolny" algorytm mnozenia(jak na kartce)
	for (uint i = 0; i < n1->size; i++)
	{
		for (uint j = 0; j < n2->size; j++)
		{
			// uzywamy formatu unsigned long long - nie dojdzie do przepelnienia
			unsigned long long pojedynczy_wynik = (unsigned long long) ((n1->data)[i]) * (unsigned long long) ((n2->data)[j]);
			wynik[i + j] = dodaj_uint(wynik[i + j], (uint)pojedynczy_wynik, flaga_przeniesienia);
			if ((((uint)(pojedynczy_wynik >> 32)) + *flaga_przeniesienia) != 0)
			{
				wynik[i + j + 1] = dodaj_uint(wynik[i + j + 1], (uint)(pojedynczy_wynik >> 32), flaga_przeniesienia);
				for (int k = i + j + 2; k < n1->size + n2->size; k++)
				{
					if (*flaga_przeniesienia == 0) break;
					wynik[k] = dodaj_uint(wynik[k], (uint)(0), flaga_przeniesienia);
				}
			}
		}

		
		
	}

	// dopasowanie rozmiaru
	n1->size = n1->size + n2->size;

	//zwalnianie dodatkowej pamieci
	//zwolnij_pamiec_uchar(&flaga_przeniesienia);
	//zwolnij_pamiec_uint(a);
	n1->data = wynik;
}

void pomnoz_przez_potege_2(Number* N, int potega)
{
	uint potega_liczby_2 = 1 << 31;


	// zaalokuj 1 + power / 32 dodatkowych uintow
	rozszerz(N, sizeof(uint) * (potega / 32 + 1));

	for (int j = N->size - 1; j >= N->size - (potega / 32 + 1); j--)
		(N->data)[j] = 0;
	
	// przesun wartosci w tablicy (mnozenie o 2 ^ 32)
	for (int j = N->size - 1; j >= potega / 32; j--)
		(N->data)[j] = (N->data)[j - (potega / 32)];
	

	// wyzeruj dolna czesc tablicy (jezeli doszlo do przesuniecia)
	for (int j = potega / 32 - 1; j >= 0; j--) 
		(N->data)[j] = 0;
	


	for (int j = N->size - 1; j >= potega / 32; j--)
	{
		potega_liczby_2 = 1 << 31;
		for (int k = potega % 32; k > 0; k--)
		{
			(N->data)[j] <<= 1;
			//przesuwamy jedynki w gore tablicy
			if (j > 0 && ((N->data)[j - 1] & potega_liczby_2) != 0)
				(N->data)[j]++;
			potega_liczby_2 >>= 1;
		}
	}


	// dopasowanie rozmiaru
	dopasuj(N);

}


void potega(Number* N, uint potega)
{
	// zmienne pomocnicze
	Number wynik;
	zaalokuj(&wynik, sizeof(uint));
	wynik.size = 1;
	*wynik.data = 1;


	// algorytm:
	// a ^ x == (a ^ 2) ^ (x / 2) (x podzielne przez 2)
	// a ^ x == a * ((a ^ 2) ^ ((x - 1) / 2)) (x niepodzielne przez 2)

	while (potega >= 1)
	{
		if (potega % 2 == 0)
			potega /= 2;
		else
		{
			pomnoz_cale_liczby(&wynik, N);
			dopasuj(&wynik);
			potega = (potega - 1) / 2;
		}


		if (potega > 0)
		{
			pomnoz_cale_liczby(N, N);
			dopasuj(N);
		}
	}
	N->size = wynik.size;

	// zwalnianie dodatkowej pamieci
	//zwolnij_pamiec_uint(&rozmiar_wyniku);
	//zwolnij_pamiec_uint(a);
	N->data = wynik.data;
}

void silnia(Number* N)
{
	if (N->size > 1)
	{
		printf("Za duzy argument dla silni!");
		exit(EXIT_FAILURE);
	}

	uint n = (N->data)[0];
	(N->data)[0] = 1;
	while (n > 1)
	{
		unsigned long long iloczyn = 1;
		while (n > 1 && iloczyn * n < UINT_MAX)
		{
			iloczyn *= n;
			n--;
		}
		pomnoz_cala_liczbe_przez_uint(N, iloczyn);
	}
	
}

