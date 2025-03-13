#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>
#include <thread>
#include <time.h>
#include <conio.h>
#include "Binaris_Kupac.h"

using namespace std;

void BeolvasPalya(string &cim, int &korok, int &hossz)
{
    ifstream f("palya.in");
    getline(f, cim);
    f >> korok >> hossz;
    f.close();
}

void BeolvasVersenyzok(vector<Driver> &drivers)
{
    ifstream f("versenyzok.in");

    string line;
    while (getline(f, line))
    {
        Driver driver;
        driver.nev = line;
        f >> driver.exp;
        f.ignore();
        getline(f, driver.car);
        f >> driver.hp >> driver.kg;
        f.ignore();
        drivers.push_back(driver);
    }

    f.close();
}

void KiirCim(string cim)
{
    cout << "---------------------------------------------" << endl;
    cout << "--->" << cim << "<---" << endl;
    cout << "---------------------------------------------" << endl
         << endl;
}

void KiirVersenyzok(vector<Driver> drivers)
{
    cout << "A Mai Futam Versenyzoi : " << endl;
    for (auto &driver : drivers)
    {
        cout << driver.nev << " -> " << driver.car << endl;
    }
    cout << endl;
}

void Start()
{
    srand(time(NULL));
    cout << "Kezdodjon is a verseny! (Enter)" << endl;
    cin.get();
}

void KiirRangsor(vector<Driver> &drivers)
{
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i].inpit == true)
        {
            cout << drivers[i].nev << " - " << drivers[i].tav << " - bokszban " << endl;
            drivers[i].inpit = false;
        }
        else
        {
            cout << drivers[i].nev << " - " << drivers[i].tav << endl;
        }
    }
    cout << endl;
}

void Dobogo(vector<Driver> drivers, string cim)
{
    cout << " A " << cim << " dobogosai a kovetkezok: " << endl
         << endl;

    cout << "                              " << drivers[0].nev << "                        " << endl;
    cout << "                         ------------------------                         " << endl;
    cout << "                         |           1          |                         " << endl;
    cout << "                         |                      |                         " << endl;
    cout << "                         |                      |                         " << endl;
    cout << "    " << drivers[1].nev << "                                                      " << endl;
    cout << "----------------------                          |                         " << endl;
    cout << "|          2                                    |                         " << endl;
    cout << "|                                               |                         " << endl;
    cout << "|                                               |   " << drivers[2].nev << endl;
    cout << "|                                              --------------------" << endl;
    cout << "|                                                        3         " << endl;
    cout << endl;

    for (int i = 3; i < drivers.size(); i++)
    {
        cout << i + 1 << ". " << drivers[i].nev << endl;
    }

    ofstream out("nyertesek.out");
    out << " A " << cim << " dobogosai a kovetkezok: " << std::endl
        << std::endl;

    out << "                              " << drivers[0].nev << "                        " << std::endl;
    out << "                         ------------------------                         " << std::endl;
    out << "                         |           1          |                         " << std::endl;
    out << "                         |                      |                         " << std::endl;
    out << "                         |                      |                         " << std::endl;
    out << "    " << drivers[1].nev << "                                                      " << std::endl;
    out << "----------------------                          |                         " << std::endl;
    out << "|          2                                    |                         " << std::endl;
    out << "|                                               |                         " << std::endl;
    out << "|                                               |   " << drivers[2].nev << std::endl;
    out << "|                                              --------------------" << std::endl;
    out << "|                                                        3         " << std::endl;
    out << std::endl;

    for (int i = 3; i < drivers.size(); i++)
    {
        out << i + 1 << ". " << drivers[i].nev << std::endl;
    }

    out.close();
}

int Random(Driver driver)
{
    double constant = (double)driver.hp / (double)driver.kg - 1.0;
    double personal = (double)constant * (double)driver.exp;
    int speed = personal / 10;
    return speed;
}

void Verseny(vector<Driver> &drivers, int fulltrack, int hossz, int korok, string cim)
{
    Start();
    system("cls");
    int seconds = 0;
    int poz = 20;
    int oldlap = 1;
    bool safety_car = false;
    while (true)
    {
        bool vege = true;
        for (int i = 0; i < drivers.size(); i++)
        {
            if (safety_car)
            {
                if (drivers[i].tav < fulltrack)
                {
                    int tmp = 102; // 34 m/s ~= 120 km/h
                    drivers[i].tav += tmp;
                    if (drivers[i].tav < fulltrack)
                    {
                        vege = false;
                    }
                }
            }
            else
            {
                if (drivers[i].tav < fulltrack)
                {

                    int pit = rand() % 100 + 1;
                    if (pit <= 5 && oldlap > 1)
                    {
                        drivers[i].inpit = true;
                        i++;
                    }
                    else
                    {
                        int tmp = Random(drivers[i]) * 3;
                        int luck = rand() % 30;
                        tmp += luck;
                        if (drivers[i].tav + tmp >= fulltrack)
                        {
                            drivers[i].tav = fulltrack + poz;
                            poz--;
                        }
                        else
                        {
                            drivers[i].tav += tmp;
                            if (drivers[i].tav < fulltrack)
                            {
                                vege = false;
                            }
                        }
                    }
                }
            }
        }

        if (vege)
        {
            break;
        }

        HeapSort(drivers);

        int lap = drivers[0].tav / hossz + 1;
        if (lap > oldlap)
        {
           
                oldlap = lap;
            

            seconds = 0;
            safety_car = false;
        }
        int safety_rand = rand() % 1000 + 1;
        seconds += 3;

        if (drivers[0].tav > fulltrack)
        {
            oldlap = korok;
        }

        std::cout << "Rangsor a " << oldlap << ". kor " << seconds << ". masodperceben :" << endl;

        if (safety_rand == 1 && oldlap < korok - 1 && oldlap > 1)
        {
            safety_car = true;
        }

        if (safety_car)
        {
            cout << "Biztonsagi auto!" << endl;
        }

        KiirRangsor(drivers);
        this_thread::sleep_for(chrono::seconds(3));
        system("cls");
    }

    Dobogo(drivers, cim);
}

int main()
{
    string cim;
    int korok, hossz;
    BeolvasPalya(cim, korok, hossz);
    int fulltrack = korok * hossz;

    vector<Driver> drivers;
    BeolvasVersenyzok(drivers);

    KiirCim(cim);
    KiirVersenyzok(drivers);

    Verseny(drivers, fulltrack, hossz, korok, cim);

    return 0;
}
