#include "komputer.h"
#include "plansza.h"
#include <cstdlib>

Komputer::Komputer(string n, char z) : Gracz(n, z)
{

}

void Komputer::wykonajRuch(Plansza* plansza, int x, int y)
{
    char wrog;

    if (znak == 'X')
    {
        wrog = 'O';
    }
    else
    {
        wrog = 'X';
    }

    // atak i obrona

    char sprawdzaneZnaki[2] = {znak, wrog};
    //dzieki temu sprawdzamy jednym kodem 2 te same rzeczy ale dla roznych stron

    for (int k = 0; k < 2; k++)
    {
        char cel = sprawdzaneZnaki[k];

        // Sprawdzanie wierszy i kolumn
        for (int i = 0; i < 3; i++)
        {
            // Sprawdzanie poziomu
            if (plansza->sprawdzPole(i, 0) == cel &&
                plansza->sprawdzPole(i, 1) == cel && plansza->czyPustePole(i, 2))
            {
                plansza->postawZnacznik(i, 2, znak); return;
            }
            if (plansza->sprawdzPole(i, 0) == cel &&
                plansza->sprawdzPole(i, 2) == cel && plansza->czyPustePole(i, 1))
            {
                plansza->postawZnacznik(i, 1, znak); return;
            }
            if (plansza->sprawdzPole(i, 1) == cel &&
                plansza->sprawdzPole(i, 2) == cel && plansza->czyPustePole(i, 0))
            {
                plansza->postawZnacznik(i, 0, znak); return;
            }

            // Sprawdzanie pionu
            if (plansza->sprawdzPole(0, i) == cel &&
                plansza->sprawdzPole(1, i) == cel && plansza->czyPustePole(2, i))
            {
                plansza->postawZnacznik(2, i, znak); return;
            }
            if (plansza->sprawdzPole(0, i) == cel &&
                plansza->sprawdzPole(2, i) == cel && plansza->czyPustePole(1, i))
            {
                plansza->postawZnacznik(1, i, znak); return;
            }
            if (plansza->sprawdzPole(1, i) == cel &&
                plansza->sprawdzPole(2, i) == cel && plansza->czyPustePole(0, i))
            {
                plansza->postawZnacznik(0, i, znak); return;
            }
        }

        // Sprawdzanie glownej przekątnej
        if (plansza->sprawdzPole(0, 0) == cel &&
            plansza->sprawdzPole(1, 1) == cel && plansza->czyPustePole(2, 2))
        {
            plansza->postawZnacznik(2, 2, znak); return;
        }
        if (plansza->sprawdzPole(0, 0) == cel &&
            plansza->sprawdzPole(2, 2) == cel && plansza->czyPustePole(1, 1))
        {
            plansza->postawZnacznik(1, 1, znak); return;
        }
        if (plansza->sprawdzPole(1, 1) == cel &&
            plansza->sprawdzPole(2, 2) == cel && plansza->czyPustePole(0, 0))
        {
            plansza->postawZnacznik(0, 0, znak); return;
        }

        // Sprawdzanie drugiej przekątnej
        if (plansza->sprawdzPole(0, 2) == cel &&
            plansza->sprawdzPole(1, 1) == cel && plansza->czyPustePole(2, 0))
        {
            plansza->postawZnacznik(2, 0, znak); return;
        }
        if (plansza->sprawdzPole(0, 2) == cel &&
            plansza->sprawdzPole(2, 0) == cel && plansza->czyPustePole(1, 1))
        {
            plansza->postawZnacznik(1, 1, znak); return;
        }
        if (plansza->sprawdzPole(1, 1) == cel &&
            plansza->sprawdzPole(2, 0) == cel && plansza->czyPustePole(0, 2))
        {
            plansza->postawZnacznik(0, 2, znak); return;
        }
    }

    //stawaianie znaku obok swojego znaku
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (plansza->sprawdzPole(i, j) == znak)
            {
                //sprawdzenie pol sąsiadujacych
                if (i > 0 && plansza->czyPustePole(i - 1, j)) //Góra
                {
                    plansza->postawZnacznik(i - 1, j, znak);
                    return;
                }

                if (i < 2 && plansza->czyPustePole(i + 1, j)) //Dól
                {
                    plansza->postawZnacznik(i + 1, j, znak);
                    return;
                }

                if (j > 0 && plansza->czyPustePole(i, j - 1)) //lewo
                {
                    plansza->postawZnacznik(i, j - 1, znak);
                    return;
                }

                if (j < 2 && plansza->czyPustePole(i, j + 1)) //prawo
                {
                    plansza->postawZnacznik(i, j + 1, znak);
                    return;
                }
            }
        }
    }

//a tutaj losowanie
    int losX, losY;
    do {
        losX = rand() % 3;
        losY = rand() % 3;
    } while (!plansza->czyPustePole(losX, losY));

    plansza->postawZnacznik(losX, losY, znak);
}
