#include "pamiec.h"
#include <stdio.h>


uint* zaalokuj_pamiec_uint(size_t rozmiar)
{
	uint* wsk = malloc(rozmiar);
	// zapobieganie bledu niewystarczajacej ilosci pamieci
	if (wsk == NULL)
	{
		printf("blad: nie udalo sie zaalokowac pamieci do zmiennej (oczekiwano %zd bajtow wolnej pamieci)", rozmiar);
		exit(EXIT_FAILURE);
	}
	return wsk;
}

int* zaalokuj_pamiec_int(size_t rozmiar)
{
	int* wsk = malloc(rozmiar);
	// zapobieganie bledu niewystarczajacej ilosci pamieci
	if (wsk == NULL)
	{
		printf("blad: nie udalo sie zaalokowac pamieci do zmiennej (oczekiwano %zd bajtow wolnej pamieci)", rozmiar);
		exit(EXIT_FAILURE);
	}
	return wsk;
}

unsigned char* zaalokuj_pamiec_char(size_t rozmiar)
{
	char* wsk = malloc(rozmiar);
	// zapobieganie bledu niewystarczajacej ilosci pamieci
	if (wsk == NULL)
	{
		printf("blad: nie udalo sie zaalokowac pamieci do zmiennej (oczekiwano %zd bajtow wolnej pamieci)", rozmiar);
		exit(EXIT_FAILURE);
	}
	return wsk;
}

void rozszerz_pamiec(unsigned int** wsk, unsigned int* rozmiar, size_t rozszerzenie)
{
	uint* pamiec = realloc(*wsk, (sizeof(unsigned int) * ((*rozmiar) + rozszerzenie)));
	// zapobieganie bledu niewystarczajacej ilosci pamieci
	if (pamiec == NULL)
	{
		printf("blad: nie udalo sie zaalokowac pamieci do zmiennej o adresie %p (oczekiwano %zd bajtow wolnej pamieci)", *wsk, sizeof(unsigned int) * (*rozmiar) + rozszerzenie);
		exit(EXIT_FAILURE);
	}
	else
	{
		*wsk = pamiec;
		(*rozmiar) += rozszerzenie;
	}
}


void dopasuj_pamiec(unsigned int** wsk, unsigned int* rozmiar)
{
	//zwalnianie zbednej pamieci (przoduj�cych zer)
	unsigned int nowy_rozmiar = *rozmiar - 1;
	while ((*wsk)[nowy_rozmiar] == 0 && nowy_rozmiar > 0) 
		nowy_rozmiar--;
	if (*rozmiar - 1 > nowy_rozmiar) *wsk = realloc(*wsk, sizeof(unsigned int) * (nowy_rozmiar + 1));
	*rozmiar = nowy_rozmiar + 1;
}

void zwolnij_pamiec_uint(uint** wsk)
{
	// zapobieganie bledu zwalniania zwolnionej juz wczesniej pamieci
	if (*wsk != NULL)
	{
		free(*wsk);
		*wsk = NULL;
	}
}

void zwolnij_pamiec_int(int** wsk)
{
	// zapobieganie bledu zwalniania zwolnionej juz wczesniej pamieci
	if (*wsk != NULL)
	{
		free(*wsk);
		*wsk = NULL;
	}
}

void zwolnij_pamiec_uchar(unsigned char** wsk)
{
	// zapobieganie bledu zwalniania zwolnionej juz wczesniej pamieci
	if (*wsk != NULL)
	{
		free(*wsk);
		*wsk = NULL;
	}
}


void zwolnij_pamiec_char(char** wsk)
{
	// zapobieganie bledu zwalniania zwolnionej juz wczesniej pamieci
	if (*wsk != NULL)
	{
		free(*wsk);
		*wsk = NULL;
	}
}



