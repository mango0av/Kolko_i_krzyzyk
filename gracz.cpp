#include "gracz.h"

Gracz::Gracz(string n, char z)
{
    nick = n;
    znak = z;
    wygrane = 0;
}

char Gracz::pobierzZnak()
{
    return znak;
}
string Gracz::pobierzNick()
{
    return nick;
}
void Gracz::dodajWygrana()
{
    wygrane++;
}

int Gracz::pobierzWygrane()
{
    return wygrane;
}

void Gracz::ustawZnak(char z)
{
    znak = z;
}

