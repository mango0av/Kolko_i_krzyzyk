#ifndef CZLOWIEK_H
#define CZLOWIEK_H
#include "gracz.h"
#include <string>

using namespace std;

class Plansza;

class Czlowiek : public Gracz
{
public:
    Czlowiek(string n, char z);
    void wykonajRuch(Plansza* plansza, int x, int y) override;
};

#endif // CZLOWIEK_H
