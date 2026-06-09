#ifndef PLANSZA_H
#define PLANSZA_H
#include <queue>
#include <utility>

class Plansza
{
public:
    Plansza();
    void wyczysc();
    void postawZnacznik(int x, int y, char znak);
    bool sprawdzWygrana(char znak);
    bool czyPustePole(int x, int y);
    char sprawdzPole(int x, int y);
    std::pair<int, int> sprawdzNajstarszyRuch(char znak);

private:
    char tab[3][3];
    std::queue<std::pair<int, int>> ruchyO;
    std::queue<std::pair<int, int>> ruchyX;
};

#endif // PLANSZA_H
