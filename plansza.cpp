#include "plansza.h"

Plansza::Plansza()
{
    wyczysc();
}

void Plansza::wyczysc()
{
//element 1: czyszczenie planszy

for (int i =0; i<3; i++)
{
    for(int j =0; j<3; j++)
    {
            tab[i][j] = ' ';
    }
}

//element 2: reset kolejek graczy

while(!ruchyX.empty())
{
    ruchyX.pop();
}

while(!ruchyO.empty())
{
    ruchyO.pop();
}

}

void Plansza::postawZnacznik(int x, int y, char znak)
{
//postawienie znaku
    tab[x][y] = znak;

//zapis do kolejki
    if (znak == 'X')
    {
        ruchyX.push({x, y});

        //usuniecie najstarszego znacznika
        if(ruchyX.size() > 3)
        {
            int staryx;
            int staryy;
            staryx = ruchyX.front().first;
            staryy = ruchyX.front().second;

            tab[staryx][staryy] = ' ';
            ruchyX.pop();
        }
    }
    else
    {
        ruchyO.push({x, y});

        //usuniecie najstarszego znacznika
        if(ruchyO.size() > 3)
        {
            int staryx;
            int staryy;
            staryx = ruchyO.front().first;
            staryy = ruchyO.front().second;

            tab[staryx][staryy] = ' ';
            ruchyO.pop();
        }
    }


}

bool Plansza::sprawdzWygrana(char znak)
{
    for(int i = 0; i < 3; i++)
    {
        if(tab[i][0] == znak && tab[i][1] == znak && tab[i][2] == znak)
            return true;

        if(tab[0][i] == znak && tab[1][i] == znak && tab[2][i] == znak)
            return true;
    }

    if(tab[0][0] == znak && tab[1][1] == znak && tab[2][2] == znak)
        return true;
    if(tab[0][2] == znak && tab[1][1] == znak && tab[2][0] == znak)
        return true;

    return false;
}

bool Plansza::czyPustePole(int x, int y)
{
    if (tab[x][y] == ' ')
        return true;
    else
        return false;
}

//aby algorytm komputera wiedzial czy to pole nie tylko jest puste
//ale tez jaki znak sie tam znajduje

char Plansza::sprawdzPole(int x, int y)
{
    return tab[x][y];
}

std::pair<int, int> Plansza::sprawdzNajstarszyRuch(char znak)
{
    if (znak == 'O' && ruchyO.size() == 3) return ruchyO.front();
    if (znak == 'X' && ruchyX.size() == 3) return ruchyX.front();

    return std::make_pair(-1, -1);
}
