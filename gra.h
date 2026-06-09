#ifndef GRA_H
#define GRA_H
#include "plansza.h"
#include <string>

class Gracz;

using namespace std;

class Gra
{
public:
    Gra();
    ~Gra();
    void uruchomPvP(string nick1, string nick2);
    void uruchomPvE(string nick1);
    void obsluzKlikniecie(int x, int y);
    string pobierzNickAktualnego();
    string pobierzNickGracza(int nr);
    int pobierzWynikGracza(int nr);
    char pobierzZnakZPlanszy(int x, int y);
    void zrestartujGre();
    std::pair<int, int> pobierzZnikajacePole();
    bool czyGraTrwa();

private:
    Plansza planszaDoGry;
    Gracz* graczNr1;
    Gracz* graczNr2;
    Gracz* aktualnyGracz;
    bool czyTrwaGra;
};

#endif // GRA_H
