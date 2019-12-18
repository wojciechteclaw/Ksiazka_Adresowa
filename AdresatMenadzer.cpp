#include "AdresatMenadzer.h"

Adresat AdresatMenadzer::podajDaneNowegoAdresata()
{
    /////////// BRAK przypisywania siê numeru ostatniego adresata z listy
    Adresat adresat;
    int idOstatniegoAdresata = plikZAdresatami.pobierzIdOstatniegoAdresata();
    adresat.ustawId(idOstatniegoAdresata + 1);
    int idZalogowanegoUzytkownika = plikZAdresatami.pobierzIdZalogowanegoUzytkownika();
    adresat.ustawIdUzytkownika(idZalogowanegoUzytkownika);

    string tekstDoWczytania;
    cout << "Podaj imie: ";
    tekstDoWczytania = MetodyPomocnicze::wczytajLinie();
    adresat.ustawImie(MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(tekstDoWczytania));

    cout << "Podaj nazwisko: ";
    tekstDoWczytania = MetodyPomocnicze::wczytajLinie();
    adresat.ustawNazwisko(MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(tekstDoWczytania));

    cout << "Podaj numer telefonu: ";
    tekstDoWczytania = MetodyPomocnicze::wczytajLinie();
    adresat.ustawNumerTelefonu(tekstDoWczytania);

    cout << "Podaj email: ";
    tekstDoWczytania = MetodyPomocnicze::wczytajLinie();
    adresat.ustawEmail(tekstDoWczytania);

    cout << "Podaj adres: ";
    tekstDoWczytania = MetodyPomocnicze::wczytajLinie();
    adresat.ustawAdres(tekstDoWczytania);

    return adresat;
}

void AdresatMenadzer::dodajAdresata()
{
    Adresat adresat;

    system("cls");
    cout << " >>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;
    adresat = podajDaneNowegoAdresata();
    adresaci.push_back(adresat);
    plikZAdresatami.dopiszAdresataDoPliku(adresat);
}

void AdresatMenadzer::wyswietlWszystkichAdresatow()
{
    system("cls");
    if (!adresaci.empty())
    {
        cout << "             >>> ADRESACI <<<" << endl;
        cout << "-----------------------------------------------" << endl;
        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            itr -> wyswietlDaneAdresata();
        }
        cout << endl;
    }
    else
    {
        cout << endl << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void AdresatMenadzer::wczytajKontaktyUzytkownika()
{
    plikZAdresatami.wczytajAdresatowZalogowanegoUzytkownikaZPliku(adresaci);
}

void AdresatMenadzer::wyszukajAdresatowPoImieniu()
{
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW O IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        imiePoszukiwanegoAdresata = MetodyPomocnicze::wczytajLinie();
        imiePoszukiwanegoAdresata = MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(imiePoszukiwanegoAdresata);

        for (vector <Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> pobierzImie() == imiePoszukiwanegoAdresata)
            {
                itr -> wyswietlDaneAdresata();
                iloscAdresatow++;
            }
        }
        wyswietlIloscWyszukanychAdresatow(iloscAdresatow);
    }
    else
    {
        cout << endl << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void AdresatMenadzer::wyswietlIloscWyszukanychAdresatow(int iloscAdresatow)
{
    if (iloscAdresatow == 0)
        cout << endl << "W ksiazce adresowej nie ma adresatow z tymi danymi." << endl;
    else
        cout << endl << "Ilosc adresatow w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
}
