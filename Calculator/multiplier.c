#include "multiplier.h"
#include <string.h>

void pomnoz_cala_liczbe_przez_uint(uint** a, uint b, uint* rozmiar_a)
{
	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	// uzywamy formatu unsigned long long - nie dojdzie do przepelnienia
	unsigned long long pojedynczy_wynik = (unsigned long long) ((*a)[0]) * (unsigned long long) (b);


	//alokacja pamieci na caly wynik 
	rozszerz_pamiec(a, rozmiar_a, 1);
	(*a)[*rozmiar_a - 1] = 0;
	(*a)[0] = 0;

	
	// "szkolny" algorytm mnozenia (jak na kartce)
	for (uint i = 0; i < *rozmiar_a - 1; i++)
	{
		uint pamiec = (*a)[i + 1];
		(*a)[i] = dodaj_uint((*a)[i], (uint)pojedynczy_wynik, flaga_przeniesienia);
		(*a)[i + 1] = dodaj_uint(0, (uint)(pojedynczy_wynik >> 32), flaga_przeniesienia);

		pojedynczy_wynik = (unsigned long long) (pamiec) * (unsigned long long) (b);
		if (*flaga_przeniesienia != 0)
		{
			pojedynczy_wynik += ((unsigned long long)(1) << 32);
			*flaga_przeniesienia = 0;
		}
	}

	// zmniejszanie rozmiaru wyniku (jezeli jest taka potrzeba)
	dopasuj_pamiec(a, rozmiar_a);
}

void pomnoz_cale_liczby(uint** a, uint** b, uint* rozmiar_a, uint* rozmiar_b)
{
	// alokacja pamieci na iloczyn
	uint* wynik = zaalokuj_pamiec_uint(sizeof(uint) * (*rozmiar_a + *rozmiar_b));
	memset(wynik, 0, sizeof(uint) * (*rozmiar_a + *rozmiar_b));

	unsigned char* flaga_przeniesienia = zaalokuj_pamiec_char(sizeof(unsigned char));
	*flaga_przeniesienia = 0;

	//"szkolny" algorytm mnozenia(jak na kartce)
	for (uint i = 0; i < *rozmiar_a; i++)
	{
		for (uint j = 0; j < *rozmiar_b; j++)
		{
			// uzywamy formatu unsigned long long - nie dojdzie do przepelnienia
			unsigned long long pojedynczy_wynik = (unsigned long long) ((*a)[i]) * (unsigned long long) ((*b)[j]);
			wynik[i + j] = dodaj_uint(wynik[i + j], (uint)pojedynczy_wynik, flaga_przeniesienia);
			if ((((uint)(pojedynczy_wynik >> 32)) + *flaga_przeniesienia) != 0)
			{
				wynik[i + j + 1] = dodaj_uint(wynik[i + j + 1], (uint)(pojedynczy_wynik >> 32), flaga_przeniesienia);
				for (int k = i + j + 2; k < *rozmiar_a + *rozmiar_b; k++)
				{
					if (*flaga_przeniesienia == 0) break;
					wynik[k] = dodaj_uint(wynik[k], (uint)(0), flaga_przeniesienia);
				}
			}
		}

		
		
	}

	// dopasowanie rozmiaru
	*rozmiar_a = *rozmiar_a + *rozmiar_b;

	//zwalnianie dodatkowej pamieci
	zwolnij_pamiec_uchar(&flaga_przeniesienia);
	zwolnij_pamiec_uint(a);
	*a = wynik;
}

void pomnoz_przez_potege_2(uint** a, int potega, uint* rozmiar_a)
{
	uint potega_liczby_2 = 1 << 31;


	// zaalokuj 1 + power / 32 dodatkowych uintow
	rozszerz_pamiec(a, rozmiar_a, potega / 32 + 1);

	for (int j = *rozmiar_a - 1; j >= *rozmiar_a - (potega / 32 + 1); j--)
		(*a)[j] = 0;
	
	// przesun wartosci w tablicy (mnozenie o 2 ^ 32)
	for (int j = *rozmiar_a - 1; j >= potega / 32; j--)
		(*a)[j] = (*a)[j - (potega / 32)];
	

	// wyzeruj dolna czesc tablicy (jezeli doszlo do przesuniecia)
	for (int j = potega / 32 - 1; j >= 0; j--) 
		(*a)[j] = 0;
	


	for (int j = *rozmiar_a - 1; j >= potega / 32; j--)
	{
		potega_liczby_2 = 1 << 31;
		for (int k = potega % 32; k > 0; k--)
		{
			(*a)[j] <<= 1;
			//przesuwamy jedynki w gore tablicy
			if (j > 0 && ((*a)[j - 1] & potega_liczby_2) != 0)
				(*a)[j]++;
			potega_liczby_2 >>= 1;
		}
	}


	// dopasowanie rozmiaru
	dopasuj_pamiec(a, rozmiar_a);

}


void potega(uint** a, uint potega, uint* rozmiar_a)
{
	// zmienne pomocnicze
	uint* wynik = zaalokuj_pamiec_uint(sizeof(uint));
	*wynik = 1;
	uint* rozmiar_wyniku = zaalokuj_pamiec_uint(sizeof(uint));
	*rozmiar_wyniku = 1;


	// algorytm:
	// a ^ x == (a ^ 2) ^ (x / 2) (x podzielne przez 2)
	// a ^ x == a * ((a ^ 2) ^ ((x - 1) / 2)) (x niepodzielne przez 2)

	while (potega >= 1)
	{
		if (potega % 2 == 0)
			potega /= 2;
		else
		{
			pomnoz_cale_liczby(&wynik, a, rozmiar_wyniku, rozmiar_a);
			dopasuj_pamiec(&wynik, rozmiar_wyniku);
			potega = (potega - 1) / 2;
		}


		if (potega > 0)
		{
			pomnoz_cale_liczby(a, a, rozmiar_a, rozmiar_a);
			dopasuj_pamiec(a, rozmiar_a);
		}
	}
	*rozmiar_a = *rozmiar_wyniku;

	// zwalnianie dodatkowej pamieci
	zwolnij_pamiec_uint(&rozmiar_wyniku);
	zwolnij_pamiec_uint(a);
	*a = wynik;
}

