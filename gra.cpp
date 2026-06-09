#include "gra.h"
#include "czlowiek.h"
#include "komputer.h"
#include <ctime>

Gra::Gra()
{
    srand(time(NULL));
    graczNr1 = nullptr;
    graczNr2 = nullptr;
    aktualnyGracz = nullptr;
    czyTrwaGra = false;
}

Gra::~Gra() //zabespieczenie
{
    if (graczNr1 != nullptr) delete graczNr1;
    if (graczNr2 != nullptr) delete graczNr2;
}

void Gra::uruchomPvP(string nick1, string nick2)
{
    //czyszczenie
    if (graczNr1 != nullptr) delete graczNr1;
    if (graczNr2 != nullptr) delete graczNr2;

    //losowanie stron
    if (rand() % 2 == 0)
    {
        graczNr1 = new Czlowiek(nick1, 'O');
        graczNr2 = new Czlowiek(nick2, 'X');
        aktualnyGracz = graczNr1;
    }
    else
    {
        graczNr1 = new Czlowiek(nick1, 'X');
        graczNr2 = new Czlowiek(nick2, 'O');
        aktualnyGracz = graczNr2;
    }

    //reset
    planszaDoGry.wyczysc();
    czyTrwaGra = true;
}

void Gra::uruchomPvE(string nick1)
{
    //czyszczenie
    if (graczNr1 != nullptr) delete graczNr1;
    if (graczNr2 != nullptr) delete graczNr2;

    //losowanie dla gry z komputerem
    if (rand() % 2 == 0)
    {
        graczNr1 = new Czlowiek(nick1, 'O');
        graczNr2 = new Komputer("Komputer", 'X');
        aktualnyGracz = graczNr1;
    }
    else
    {
        graczNr1 = new Czlowiek(nick1, 'X');
        graczNr2 = new Komputer("Komputer", 'O');
        aktualnyGracz = graczNr2;
    }

    //reset
    planszaDoGry.wyczysc();
    czyTrwaGra = true;
}

void Gra::obsluzKlikniecie(int x, int y)
{
    if (czyTrwaGra == false)
    {
        return;
    }

    if (planszaDoGry.czyPustePole(x, y) == true)
    {
//ruch
        aktualnyGracz->wykonajRuch(&planszaDoGry, x, y);

//czy wygrana
        if (planszaDoGry.sprawdzWygrana(aktualnyGracz->pobierzZnak()) == true)
        {
            czyTrwaGra = false;
            aktualnyGracz->dodajWygrana();  //dodanie zwyciestwa do rankingu
        }
        else
        {
            //tura trwa dalej
            if (aktualnyGracz == graczNr1)
            {
                aktualnyGracz = graczNr2;
            }
            else
            {
                aktualnyGracz = graczNr1;
            }

            if (czyTrwaGra == true && aktualnyGracz->pobierzNick() == "Komputer")
            {
                //bot ma zignorrowac
                aktualnyGracz->wykonajRuch(&planszaDoGry, -1, -1);

                if (planszaDoGry.sprawdzWygrana(aktualnyGracz->pobierzZnak()) == true)
                {
                    czyTrwaGra = false;
                    aktualnyGracz->dodajWygrana();
                }
                else
                {
                    if (aktualnyGracz == graczNr1)
                    {
                        aktualnyGracz = graczNr2;
                    }
                    else
                    {
                        aktualnyGracz = graczNr1;
                    }
                }
            }
        }
    }
}

string Gra::pobierzNickAktualnego()
{
    if (aktualnyGracz != nullptr)
    {
        return aktualnyGracz->pobierzNick();
    }
    return "Oczekiwanie...";
}

string Gra::pobierzNickGracza(int nr)
{
    if (nr == 1 && graczNr1 != nullptr) return graczNr1->pobierzNick();
    if (nr == 2 && graczNr2 != nullptr) return graczNr2->pobierzNick();
    return "-";
}

int Gra::pobierzWynikGracza(int nr)
{
    if (nr == 1 && graczNr1 != nullptr) return graczNr1->pobierzWygrane();
    if (nr == 2 && graczNr2 != nullptr) return graczNr2->pobierzWygrane();
    return 0;
}

char Gra::pobierzZnakZPlanszy(int x, int y)
{
    return planszaDoGry.sprawdzPole(x, y);
}

void Gra::zrestartujGre()
{
    planszaDoGry.wyczysc();
    czyTrwaGra = true;

    if (graczNr1 != nullptr && graczNr2 != nullptr)
    {

        char znak1 = graczNr1->pobierzZnak();
        char znak2 = graczNr2->pobierzZnak();

        graczNr1->ustawZnak(znak2);
        graczNr2->ustawZnak(znak1);

        if (graczNr1->pobierzZnak() == 'O')
        {
            aktualnyGracz = graczNr1;
        } else
        {
            aktualnyGracz = graczNr2;
        }
    }
}

std::pair<int, int> Gra::pobierzZnikajacePole()
{
    if (aktualnyGracz != nullptr)
    {
        return planszaDoGry.sprawdzNajstarszyRuch(aktualnyGracz->pobierzZnak());
    }
    return std::make_pair(-1, -1);
}

bool Gra::czyGraTrwa()
{
    return czyTrwaGra;
}
