#ifndef NUMBER_H_   
#define NUMBER_H_   

#include <stdlib.h>

typedef struct Number
{
    unsigned* data;
    unsigned size;
} Number;



void zaalokuj(Number* nr, size_t rozmiar);
void rozszerz(Number* nr, int nowy_rozmiar);
void dopasuj(Number* nr);
void zwolnij(Number* nr);



#endif