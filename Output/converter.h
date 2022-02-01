#pragma once
#include "Utility/pamiec.h"
#include <stdio.h>



void zamien_na_dowolna_baze(unsigned int podstawa, unsigned int** liczba, unsigned int rozmiar);
void zamien_na_bin(unsigned int** liczba, unsigned int rozmiar);
void zamien_na_hex(unsigned int** liczba, unsigned int rozmiar);

void inteligentna_zamiana(unsigned int podstawa, unsigned int** liczba, unsigned int rozmiar);