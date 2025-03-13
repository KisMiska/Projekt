#include <iostream>
#include "Binaris_Kupac.h"
#include <cmath>
using namespace std;

Binaris_kupac *CreateKupac()
{
    Binaris_kupac *uj = new Binaris_kupac;
    return uj;
}

void DestroyKupac(Binaris_kupac *kupac)
{
    delete kupac;
}

int Szulo(int i)
{
    return (i - 1) / 2;
}

int BalGyerek(int i)
{
    return 2 * i + 1;
}

int JobbGyerek(int i)
{
    return 2 * i + 2;
}

void Csere(Driver &a, Driver &b)
{
    Driver temp = a;
    a = b;
    b = temp;
}

bool HasDrivers(Driver a, Driver b)
{
    return (a.tav < b.tav);
}

void Kupacol(Binaris_kupac *kupac, int i)
{
    int bal = BalGyerek(i);
    int jobb = JobbGyerek(i);

    int max = i;
    if (bal < kupac->kupac.size() && HasDrivers(kupac->kupac[bal], kupac->kupac[max]))
    {
        max = bal;
    }
    if (jobb < kupac->kupac.size() && HasDrivers(kupac->kupac[jobb], kupac->kupac[max]))
    {
        max = jobb;
    }

    if (max != i)
    {
        Csere(kupac->kupac[i], kupac->kupac[max]);
        Kupacol(kupac, max);
    }
}

void Beszur(Binaris_kupac *kupac, Driver value)
{
    kupac->kupac.push_back(value);
    int i = kupac->kupac.size() - 1;

    while (i > 0 && HasDrivers(kupac->kupac[Szulo(i)], kupac->kupac[i]))
    {
        Csere(kupac->kupac[i], kupac->kupac[Szulo(i)]);
        i = Szulo(i);
    }
}

void Torol(Binaris_kupac *kupac)
{
    if (kupac->kupac.empty())
    {
        return;
    }

    kupac->kupac[0] = kupac->kupac.back();
    kupac->kupac.pop_back();
    Kupacol(kupac, 0);
}

void KiirKupac(Binaris_kupac *kupac)
{
    for (int i = 0; i < kupac->kupac.size(); i++)
    {
        cout << kupac->kupac[i].nev << endl;
        cout << kupac->kupac[i].car << endl;
        cout << kupac->kupac[i].exp << endl;
        cout << kupac->kupac[i].hp << endl;
        cout << kupac->kupac[i].kg << endl;
        cout << kupac->kupac[i].tav << endl;
        cout << endl;
    }
    cout << endl;
}

Binaris_kupac *EpitKupac(vector<Driver> &tomb)
{
    Binaris_kupac *kupac = CreateKupac();
    kupac->kupac = tomb;
    for (int i = kupac->kupac.size() / 2 - 1; i >= 0; i--)
    {
        Kupacol(kupac, i);
    }
    return kupac;
}

void HeapSort(vector<Driver> &tomb)
{

    Binaris_kupac *kupac = EpitKupac(tomb);

    for (int i = tomb.size() - 1; i >= 0; i--)
    {
        tomb[i] = kupac->kupac[0];
        Torol(kupac);
    }

    DestroyKupac(kupac);
}