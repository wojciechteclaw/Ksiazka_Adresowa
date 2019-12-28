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
    const string NAZWA_PLIKU_Z_ADRESATAMI;
    const int ID_ZALOGOWANEGO_UZYTKOWNIKA;
    string ZamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat);
    bool czyPlikJestPusty(fstream &plikTekstowy);
    int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string);
    Adresat pobierzDaneAdresata(string);
    int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string);
    int idOstatniegoAdresataPliku;

public:
    PlikZAdresatami(string nazwaPlikuZAdresatami, int idZalogowanegoUzytkownika) : NAZWA_PLIKU_Z_ADRESATAMI(nazwaPlikuZAdresatami),
    ID_ZALOGOWANEGO_UZYTKOWNIKA(idZalogowanegoUzytkownika) {};
    void dopiszAdresataDoPliku(Adresat);
    void wczytajAdresatowZalogowanegoUzytkownikaZPliku(vector <Adresat> &adresaci);
    int pobierzIdOstatniegoAdresata();
    int pobierzIdZalogowanegoUzytkownika();
    void usunAdresataZPliku(int);
    void zapiszEdytowanegoAdresata(Adresat);
};

#endif
