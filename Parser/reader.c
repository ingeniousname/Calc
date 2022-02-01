#include "reader.h"
#include <math.h>
#include <string.h>

void przeczytaj_liczbe_o_dowolnej_podstawie(int podstawa, char* bufor, uint** liczba, uint* rozmiar_liczby)
{
	

	//obliczamy rozmiar liczby i alokujemy pamiec
	*rozmiar_liczby = log(podstawa) / log(2) / 32 * (strlen(bufor)) + 1;
	*liczba = zaalokuj_pamiec_uint(sizeof(uint) * (*rozmiar_liczby));
	memset(*liczba, 0, sizeof(uint) * (*rozmiar_liczby));



	for (int i = 0; i < strlen(bufor); i++)
	{
		if (bufor[i] <= '9')
		{
			if (bufor[i] - '0' >= podstawa)
			{
				printf("blad: w liczbie o podstawie %i nie moze byc cyfry %c!", podstawa, bufor[i]);
				exit(EXIT_FAILURE);
			}
			dodaj_uint_do_calej_liczby(liczba, (uint)(bufor[i] - '0'), rozmiar_liczby);
		}
		else
		{
			if (bufor[i] - 'A' + 10 >= podstawa)
			{
				printf("blad: w liczbie o podstawie %i nie moze byc cyfry %c!", podstawa, bufor[i]);
				exit(EXIT_FAILURE);
			}
			dodaj_uint_do_calej_liczby(liczba, (uint)(bufor[i] - 'A'), rozmiar_liczby);
		}
		if(i != strlen(bufor) - 1)
			pomnoz_cala_liczbe_przez_uint(liczba, (uint)podstawa, rozmiar_liczby);
	}
}
