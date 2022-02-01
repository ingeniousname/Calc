#include "converter.h"
#include <stdio.h>
#include <math.h>
#include <string.h>


void zamien_na_dowolna_baze(unsigned int podstawa, unsigned int** liczba, unsigned int rozmiar)
{
    if (rozmiar == 0 || (rozmiar == 1 && (*liczba)[0] == 0))
    {
        printf("%c", 48);
        return;
    }

    int potega_2do16 = 1 << 16;

    //obliczanie dlugosci wynikow
    int rozmiar_nowej_liczby = rozmiar * 2 * (log(potega_2do16) / log(podstawa)) + 1;

    //alokacja miejsca na kolejne potegi podstawy (kazda cyfra miesci sie w oddzielnym incie)
    int* potega_podstawy = zaalokuj_pamiec_int(sizeof(int) * (rozmiar_nowej_liczby + 1));
    memset(potega_podstawy, 0, sizeof(int) * (rozmiar_nowej_liczby + 1));

    //alokacja miejsca na wynik (kazda cyfra miesci sie w oddzielnym incie)
    int* wynik = zaalokuj_pamiec_int(sizeof(int) * (rozmiar_nowej_liczby + 1));
    memset(wynik, 0, sizeof(int) * (rozmiar_nowej_liczby + 1));
    potega_podstawy[0] = 1; // podstawa ^ 0



    // petla musi sie wykonywac tylko tyle razy, ile niezerowych wartosci jest w tablicy cyfr potegi podstawy
    int warunek_petli = 0;




    // 
    for (int i = 0; i < rozmiar * 2; i++) 
    {
        int it = 0, pamiec, reszta = 0;
        // wynik[j] += (podstawa ^ i) * (j-ta cyfra duzej liczby w podstawie 2 ^ 16)
        // mozemy zalozyc, ze podstawa liczb zapisanych w komputerze to 2 ^ 16, dzieki temu kazdy element tablicy uintow ma tylko dwie cyfry...
        // ...ta heurystyka pozwala zmniejszyc ilosc wywolan petli (int i ...), kosztem pamieci (potrzebny jest typ danych int aby nie doszlo do przepelnienia)...
        // ...zauwazmy ze dla np dla podstawy 2 musielibysmy sprawdzac kazdy bit i oddzielnie w kazdym wywolaniu petli zwiekszac potege podstawy...
        // ...zatem dla jednego uinta zewnetrzna petla musialaby sie wykonac 32 razy, a w tym algorytmie wykonuje sie tylko 2 razy, oczywiscie...
        // ...wiecej czasu poswieca sie na wyrownywanie elementow tablicy do podstawy koncowej (tej, w ktorej chcemy aby liczba byla zapisana)...
        // ...ale po testach okazuje sie ze ten algorytm jest szybszy
        for (int j = 0; j <= warunek_petli; j++) 
            wynik[j] += potega_podstawy[j] * ((*liczba)[i / 2] % potega_2do16);
        

        pamiec = wynik[0];
        do // usuwamy reszty w podstawie wyniku 
        {
            reszta = pamiec / podstawa;
            wynik[it] = pamiec - reszta * podstawa;
            it++;
            wynik[it] += reszta;
            pamiec = wynik[it];
        } while (it <= warunek_petli || pamiec >= podstawa);



        //obliczamy kolejna potege podstawy
        for (int j = 0; j <= warunek_petli; j++)
        {
            potega_podstawy[j] = potega_podstawy[j] * potega_2do16;
        }

        pamiec = potega_podstawy[0];
        reszta = 0;
        it = 0;
        do  // usuwamy reszty w podstawie wyniku  
        {
            reszta = pamiec / podstawa;
            potega_podstawy[it] = pamiec - reszta * podstawa;
            it++;
            potega_podstawy[it] += reszta;
            pamiec = potega_podstawy[it];
        } while (it <= warunek_petli || pamiec >= podstawa);
        


        if (it > warunek_petli) warunek_petli = it;
        (*liczba)[i / 2] >>= 16;
    }

    int i = rozmiar_nowej_liczby;
    while (wynik[i] == 0) i--;

   

    for (i; i >= 0; i--)
    {
        if(wynik[i] > 9) printf("%c", 55 + wynik[i]);
        else printf("%c", 48 + wynik[i]);
    }


    zwolnij_pamiec_int(&wynik);
    zwolnij_pamiec_int(&potega_podstawy);



}

void zamien_na_bin(unsigned int** liczba, unsigned int rozmiar)
{
    int j = rozmiar * 32 - 1;
    uint potega_2 = 1 << 31;

    // pomijamy wiod�ce zera
    while (((*liczba)[j / 32] & potega_2) == 0)
    {
        j--;
        potega_2 >>= 1;
    }


    // sprawdzamy bity po kolei 
    for (j; j >= 0; j--)
    {
        if ((*liczba)[j / 32] & potega_2)
            printf("%c", '1');
        else
            printf("%c", '0');

        if (j % 32 == 0)
            potega_2 = 1 << 31;
        else potega_2 >>= 1;
    }
}



void zamien_na_hex(unsigned int** liczba, unsigned int rozmiar)
{
    // najszybszy algorytm zamiany - preferowane uzycie dla duzych liczb
    printf("%X", (*liczba)[rozmiar - 1]);
    for (int i = rozmiar - 2; i >= 0; i--)
        printf("%08X", (*liczba)[i]);
}

void inteligentna_zamiana(unsigned int podstawa, unsigned int** liczba, unsigned int rozmiar)
{
    if (podstawa < 2 || podstawa > 16)
    {
        printf("liczby o podstawie %u nie sa obslugiwane!", podstawa);
        return;
    }

    switch (podstawa)
    {
    case 2: zamien_na_bin(liczba, rozmiar); break;
    case 16: zamien_na_hex(liczba, rozmiar); break;
    default: zamien_na_dowolna_baze(podstawa, liczba, rozmiar); break;
        
    }
}



