#ifndef KUPAC_H
#define KUPAC_H

#include <vector>
#include <string>

struct Driver
{
    std::string nev;
    int exp;
    std::string car;
    int hp;
    int kg;
    int tav = 0;
    bool inpit = false;
};

typedef struct Binaris_kupac
{
    std::vector<Driver> kupac;

} Binaris_kupac;

Binaris_kupac *CreateKupac();
void DestroyKupac(Binaris_kupac *);
int Szulo(int);
int BalGyerek(int);
int JobbGyerek(int);
void Csere(Driver &, Driver &);
bool HasDrivers(Driver, Driver);
void Kupacol(Binaris_kupac *, int);
void Beszur(Binaris_kupac *, Driver);
void Torol(Binaris_kupac *);
Binaris_kupac *EpitKupac(std::vector<Driver> &);
void HeapSort(std::vector<Driver> &);
void KiirKupac(Binaris_kupac *);

#endif