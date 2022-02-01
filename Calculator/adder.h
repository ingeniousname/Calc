#pragma once
//#define uint unsigned int

#include "Utility/pamiec.h"
#include <limits.h>


uint dodaj_uint(uint a, uint b, unsigned char* flaga_przeniesienia);
void dodaj_cale_liczby(uint** a, uint** b, uint* rozmiar_a, uint* rozmiar_b);
void dodaj_uint_do_calej_liczby(uint** a, uint b, uint* rozmiar_a);

uint odejmij_uint(uint a, uint b, unsigned char* pozyczka);
void odejmij_cale_liczby(uint** a, uint** b, uint* rozmiar_a, uint* rozmiar_b);