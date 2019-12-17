#ifndef ADRESATMENADZER_H
#define ADRESATMENADZER_H
#include <iostream>
#include "Adresat.h"
#include <vector>
#include "MetodyPomocnicze.h"
#include "PlikZAdresatami.h"

class AdresatMenadzer{
    Adresat podajDaneNowegoAdresata();
    vector <Adresat> adresaci;
    PlikZAdresatami plikZAdresatami;
    void wyswietlIloscWyszukanychAdresatow(int);

public:
    AdresatMenadzer(string nazwaPlikuZAdresatami, int idZalogowanegoUzytkownika) : plikZAdresatami(nazwaPlikuZAdresatami, idZalogowanegoUzytkownika) {
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
