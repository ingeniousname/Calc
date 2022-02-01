#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "Calculator/adder.h"
#include "Calculator/multiplier.h"
#include "Output/converter.h"
#include "Calculator/division.h"
#include "Parser/reader.h"



int main(int argc, char* argv[])
{
	uint* rozmiar1 = zaalokuj_pamiec_uint(sizeof(uint));
	uint* rozmiar2 = zaalokuj_pamiec_uint(sizeof(uint));
	uint* liczba1 = NULL;
	uint* liczba2 = NULL;
	przeczytaj_liczbe_o_dowolnej_podstawie(10, argv[1], &liczba1, rozmiar1);
	przeczytaj_liczbe_o_dowolnej_podstawie(10, argv[3], &liczba2, rozmiar2);
	switch (*(argv[2]))
	{
		case '+':
		{
			dodaj_cale_liczby(&liczba1, &liczba2, rozmiar1, rozmiar2);
			break;
		}
		case '*':
		{
			pomnoz_cale_liczby(&liczba1, &liczba2, rozmiar1, rozmiar2);
			break;
		}
		case '/':
		{
			podziel(&liczba1, &liczba2, rozmiar1, rozmiar2);
			break;
		}
		case '^':
		{
			potega(&liczba1, liczba2[0], rozmiar1);
			break;
		}
		default:
		{
			printf("niezidentyfikowany operator");
			return 1;
			break;
		}
	}
			
	dopasuj_pamiec(&liczba1, rozmiar1);
	//... a nastepnie wynik
	inteligentna_zamiana(10, &liczba1, *rozmiar1);
	zwolnij_pamiec_uint(&liczba2);
	zwolnij_pamiec_uint(&liczba1);
	printf("\n");
	
	
	
	
	return 0;
}