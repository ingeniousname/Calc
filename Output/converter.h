#pragma once
#include "Utility/pamiec.h"
#include <stdio.h>
#include "Calculator/number.h"



void zamien_na_dowolna_baze(unsigned int podstawa, Number* N);
void zamien_na_bin(Number* N);
void zamien_na_hex(Number* N);

void inteligentna_zamiana(unsigned int podstawa, Number* N);