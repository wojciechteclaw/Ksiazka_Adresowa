#ifndef PLIKZADRESATAMI_H
#define PLIKZADRESATAMI_H
#include <iostream>
#include <fstream>
#include <vector>

#include "Adresat.h"
#include "MetodyPomocnicze.h"

using namespace std;


class PlikZAdresatami
{
    string ZamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat);
    bool czyPlikJestPusty(fstream &plikTekstowy);
    int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string);
    Adresat pobierzDaneAdresata(string);
    int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string);

public:
    void dopiszAdresataDoPliku(Adresat);
    int wczytajAdresatowZalogowanegoUzytkownikaZPliku(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika);
};

#endif
