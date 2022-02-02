#include "number.h"
#include <stdio.h>

void zaalokuj(Number* nr, size_t rozmiar)
{
    nr->data = malloc(sizeof(unsigned) * rozmiar);
    if(!nr->data)
	{
		printf("blad: nie udalo sie zaalokowac pamieci do zmiennej (oczekiwano %zd bajtow wolnej pamieci)", rozmiar);
		exit(EXIT_FAILURE);
	}
}

void rozszerz(Number* nr, int rozszerzenie)
{
    uint* pamiec = realloc(nr->data, (sizeof(unsigned int) * ((nr->size) + rozszerzenie)));
	// zapobieganie bledu niewystarczajacej ilosci pamieci
	if (pamiec == NULL)
	{
		printf("blad: nie udalo sie zaalokowac pamieci do zmiennej o adresie %p (oczekiwano %zd bajtow wolnej pamieci)", nr->data, sizeof(unsigned int) * (nr->size) + rozszerzenie);
		exit(EXIT_FAILURE);
	}
	else
	{
		nr->data = pamiec;
		(nr->size) += rozszerzenie;
	}
}

void dopasuj(Number* nr)
{
    //zwalnianie zbednej pamieci (przoduj�cych zer)
	unsigned int nowy_rozmiar = nr->size - 1;
	while ((nr->data)[nowy_rozmiar] == 0 && nowy_rozmiar > 0) 
		nowy_rozmiar--;
	if (nr->size - 1 > nowy_rozmiar) nr->data = realloc(nr->data, sizeof(unsigned int) * (nowy_rozmiar + 1));
	nr->size = nowy_rozmiar + 1;
}

void zwolnij(Number* nr)
{
    free(nr->data);
}