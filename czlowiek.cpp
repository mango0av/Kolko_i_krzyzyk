#include "czlowiek.h"
#include "plansza.h"

Czlowiek::Czlowiek(string n, char z) : Gracz(n, z)
{

}

void Czlowiek::wykonajRuch(Plansza* plansza, int x, int y)
{
    plansza->postawZnacznik(x, y ,znak);
}
