#pragma once
//#define uint unsigned int

#include "Utility/pamiec.h"
#include "number.h"
#include <limits.h>


uint dodaj_uint(uint a, uint b, unsigned char* flaga_przeniesienia);
void dodaj_cale_liczby(Number* n1, Number* n2);
void dodaj_uint_do_calej_liczby(Number* N, uint b);

uint odejmij_uint(uint a, uint b, unsigned char* pozyczka);
void odejmij_cale_liczby(Number* n1, Number* n2);