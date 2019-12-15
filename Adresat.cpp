#include "Adresat.h"

int Adresat::pobierzId()
{
    return id;
}

int Adresat::pobierzIdUzytkownika()
{
    return idUzytkownika;
}

string Adresat::pobierzImie()
{
    return imie;
}

string Adresat::pobierzNazwisko()
{
    return nazwisko;
}

string Adresat::pobierzNumerTelefonu()
{
    return numerTelefonu;
}

string Adresat::pobierzEmail()
{
    return email;
}

string Adresat::pobierzAdres()
{
    return adres;
}

void Adresat::ustawId(int noweId)
{
    id = noweId;
}

void Adresat::ustawIdUzytkownika(int noweIdUzytkownika)
{
    idUzytkownika = noweIdUzytkownika;
}

void Adresat::ustawImie(string noweImie)
{
    imie = noweImie;
}

void Adresat::ustawNazwisko(string noweNazwisko)
{
    nazwisko = noweNazwisko;
}

void Adresat::ustawNumerTelefonu(string nowyNumer)
{
    numerTelefonu = nowyNumer;
}

void Adresat::ustawEmail(string nowyEmail)
{
    email = nowyEmail;
}

void Adresat::ustawAdres(string nowyAdres)
{
    adres = nowyAdres;
}

void Adresat::wyswietlDaneAdresata()
{
    cout << endl << "Id:                 " << id<< endl;
    cout << "Imie:               " << imie << endl;
    cout << "Nazwisko:           " << nazwisko << endl;
    cout << "Numer telefonu:     " << numerTelefonu << endl;
    cout << "Email:              " << email << endl;
    cout << "Adres:              " << adres << endl;
}
