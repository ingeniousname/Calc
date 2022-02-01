#pragma once
#include <stdlib.h>



uint* zaalokuj_pamiec_uint(size_t rozmiar);
int* zaalokuj_pamiec_int(size_t rozmiar);
unsigned char* zaalokuj_pamiec_char(size_t rozmiar);
void rozszerz_pamiec(unsigned int** wsk, unsigned int* rozmiar, size_t rozszerzenie);
void dopasuj_pamiec(unsigned int** wsk, unsigned int* rozmiar);
void zwolnij_pamiec_uint(uint** wsk);
void zwolnij_pamiec_int(int** wsk);
void zwolnij_pamiec_uchar(unsigned char** wsk);
void zwolnij_pamiec_char(char** wsk);

