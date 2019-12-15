#ifndef METODYPOMOCNICZE_H
#define METODYPOMOCNICZE_H

#include <iostream>
#include <sstream>
#include <algorithm>

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
};

#endif
