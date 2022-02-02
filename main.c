#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "Calculator/adder.h"
#include "Calculator/multiplier.h"
#include "Output/converter.h"
#include "Calculator/division.h"
#include "Parser/reader.h"
#include "Calculator/number.h"


int main(int argc, char* argv[])
{
	Number n1, n2;
	przeczytaj_liczbe_o_dowolnej_podstawie(10, argv[1], &n1);
	if(argc > 3)
		przeczytaj_liczbe_o_dowolnej_podstawie(10, argv[3], &n2);

	switch (*(argv[2]))
	{
		case '+':
		{
			dodaj_cale_liczby(&n1, &n2);
			break;
		}
		case '*':
		{
			pomnoz_cale_liczby(&n1, &n2);
			break;
		}
		case '/':
		{
			podziel(&n1, &n2);
			break;
		}
		case '^':
		{
			potega(&n1, n2.data[0]);
			break;
		}
		case '%':
		{
			podziel_i_zwroc_modulo(&n1, &n2);
			break;
		}
		case '!':
		{
			silnia(&n1);
			break;
		}
		default:
		{
			printf("niezidentyfikowany operator");
			return 1;
			break;
		}
	}
			
	dopasuj(&n1);
	//... a nastepnie wynik
	inteligentna_zamiana(10, &n1);
	printf("\n");
	
	
	
	
	return 0;
}