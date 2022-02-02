#include "reader.h"
#include <math.h>
#include <string.h>

void przeczytaj_liczbe_o_dowolnej_podstawie(int podstawa, char* bufor, Number* N)
{
	

	//obliczamy rozmiar liczby i alokujemy pamiec
	N->size = log(podstawa) / log(2) / 32 * (strlen(bufor)) + 1;
	zaalokuj(N, sizeof(uint) * N->size);
	memset(N->data, 0, sizeof(uint) * N->size);



	for (int i = 0; i < strlen(bufor); i++)
	{
		if (bufor[i] <= '9')
		{
			if (bufor[i] - '0' >= podstawa)
			{
				printf("blad: w liczbie o podstawie %i nie moze byc cyfry %c!", podstawa, bufor[i]);
				exit(EXIT_FAILURE);
			}
			dodaj_uint_do_calej_liczby(N, (uint)(bufor[i] - '0'));
		}
		else
		{
			if (bufor[i] - 'A' + 10 >= podstawa)
			{
				printf("blad: w liczbie o podstawie %i nie moze byc cyfry %c!", podstawa, bufor[i]);
				exit(EXIT_FAILURE);
			}
			dodaj_uint_do_calej_liczby(N, (uint)(bufor[i] - 'A'));
		}
		if(i != strlen(bufor) - 1)
			pomnoz_cala_liczbe_przez_uint(N, (uint)podstawa);
	}
}
