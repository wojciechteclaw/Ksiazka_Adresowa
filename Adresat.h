#ifndef ADRESAT_H
#define ADRESAT_H
#include <iostream>
using namespace std;

class Adresat
{
    int id;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;

public:
    int pobierzId();
    int pobierzIdUzytkownika();
    string pobierzImie();
    string pobierzNazwisko();
    string pobierzNumerTelefonu();
    string pobierzEmail();
    string pobierzAdres();
    void ustawId(int);
    void ustawIdUzytkownika(int);
    void ustawImie(string);
    void ustawNazwisko(string);
    void ustawNumerTelefonu(string);
    void ustawEmail(string);
    void ustawAdres(string);
    void wyswietlDaneAdresata();
};

#endif
