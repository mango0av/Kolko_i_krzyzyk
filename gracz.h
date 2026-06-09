#ifndef GRACZ_H
#define GRACZ_H
#include <string>
using namespace std;

class Plansza;

class Gracz
{
public:
    Gracz(string n, char z);
    virtual ~Gracz() {} //zeby mozna bylo usuwac w grze.cpp
    char pobierzZnak();
    string pobierzNick();
    void dodajWygrana();
    virtual void wykonajRuch(Plansza* plansza, int x, int y) = 0;
    int pobierzWygrane();
    void ustawZnak(char z);

protected:
    char znak;
    string nick;
    int wygrane = 0;
};

#endif // GRACZ_H
