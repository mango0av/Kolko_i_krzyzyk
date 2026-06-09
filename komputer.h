#ifndef KOMPUTER_H
#define KOMPUTER_H
#include "gracz.h"
#include <string>

using namespace std;

class Plansza;

class Komputer : public Gracz
{
public:
    Komputer(string n, char z);
    virtual ~Komputer() {} //zeby mozna bylo usuwac w grze.cpp
    void wykonajRuch(Plansza* plansza, int x, int y) override;
};

#endif // KOMPUTER_H
