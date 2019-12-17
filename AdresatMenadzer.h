#ifndef ADRESATMENADZER_H
#define ADRESATMENADZER_H
#include <iostream>
#include "Adresat.h"
#include <vector>
#include "MetodyPomocnicze.h"
#include "PlikZAdresatami.h"

class AdresatMenadzer{
    int idZalogowanegoUzytkownika;
    Adresat podajDaneNowegoAdresata();
    vector <Adresat> adresaci;
    PlikZAdresatami plikZAdresatami;
    void wyswietlIloscWyszukanychAdresatow(int);
    int idOstatniegoAdresata;

public:
    AdresatMenadzer(string nazwaPlikuZAdresatami, int idZalogowanegoUzytkownika) : plikZAdresatami(nazwaPlikuZAdresatami) {
        this->idZalogowanegoUzytkownika = idZalogowanegoUzytkownika;
        wczytajKontaktyUzytkownika();
    }
    void dodajAdresata();
    void wyszukajPoImieniu();
    void wyszukajPoNazwisku();
    void wyswietlWszystkichAdresatow();
    void ustawIdZalogowanegoUzytkownika(int);
    void wczytajKontaktyUzytkownika();
    void wyszukajAdresatowPoImieniu();
};

#endif
