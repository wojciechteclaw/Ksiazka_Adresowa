#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "UzytkownikMenadzer.h"
#include "MenuInterfejs.h"
#include "AdresatMenadzer.h"

using namespace std;

class KsiazkaAdresowa
{
    UzytkownikMenadzer uzytkownikMenadzer;
    AdresatMenadzer *adresMenadzer;
    const string NAZWA_PLIKU_Z_ADRESATAMI;

public:
    KsiazkaAdresowa(string nazwaPlikuZUzytkownikami, string nazwaPlikuZAdresatami) : uzytkownikMenadzer(nazwaPlikuZUzytkownikami), NAZWA_PLIKU_Z_ADRESATAMI(nazwaPlikuZAdresatami)
    {
        adresMenadzer = NULL;
    };
    ~KsiazkaAdresowa()
    {
        delete adresMenadzer;
        adresMenadzer = NULL;
    }
    void rejestracjaUzytkownika();
    void wypiszWszystkichUzytkownikow();
    void logowanieUzytkownika();
    void wlaczProgram();
};
