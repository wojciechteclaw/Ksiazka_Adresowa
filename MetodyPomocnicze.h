#ifndef METODYPOMOCNICZE_H
#define METODYPOMOCNICZE_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

class MetodyPomocnicze
{
public:
    static string konwerjsaIntNaString(int);
    static string wczytajLinie();
    static char wczytajZnak();
    static string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string);
    static int konwersjaStringNaInt(string);
    static string pobierzLiczbe(string, int);
    static int wczytajLiczbeCalkowita();
    static void usunPlik(string);
    static void zmienNazwePliku(string, string);
};

#endif
