#ifndef ADRESATMENADZER_H
#define ADRESATMENADZER_H
#include <iostream>
#include "Adresat.h"
#include <vector>
#include "MetodyPomocnicze.h"
#include "PlikZAdresatami.h"

class AdresatMenadzer{
    int idZalogowanegoUzytkownika;
    int idOstatniegoAdresata;
    Adresat podajDaneNowegoAdresata();
    vector <Adresat> adresaci;
    PlikZAdresatami plikZAdresatami;
    void wyswietlIloscWyszukanychAdresatow(int);

public:
    AdresatMenadzer(string nazwaPlikuZAdresatami) : plikZAdresatami(nazwaPlikuZAdresatami) {}
    void dodajAdresata();
    void wyszukajPoImieniu();
    void wyszukajPoNazwisku();
    void wyswietlWszystkichAdresatow();
    void ustawIdZalogowanegoUzytkownika(int);
    void wczytajKontaktyUzytkownika();
    void wyszukajAdresatowPoImieniu();
};

#endif
