#include "KsiazkaAdresowa.h"

using namespace std;

void KsiazkaAdresowa::rejestracjaUzytkownika()
{
    uzytkownikMenadzer.rejestracjaUzytkownika();
}

void KsiazkaAdresowa::wypiszWszystkichUzytkownikow()
{
    uzytkownikMenadzer.wypiszWszystkichUzytkownikow();
}

void KsiazkaAdresowa::logowanieUzytkownika(){
    uzytkownikMenadzer.logowanieUzytkownika();
    adresMenadzer.ustawIdZalogowanegoUzytkownika(uzytkownikMenadzer.pobierzIdZalogowanegoUzytkownika());
    adresMenadzer.wczytajKontaktyUzytkownika();

}

void KsiazkaAdresowa::wlaczProgram(){
    MenuInterfejs menuInterfejs;
    while (true)
    {
        if (uzytkownikMenadzer.pobierzIdZalogowanegoUzytkownika() == 0)
        {
            char wybor = menuInterfejs.wyborZMenuGlownego();

            switch (wybor)
            {
            case '1':
                rejestracjaUzytkownika();
                break;
            case '2':
                logowanieUzytkownika();
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        }
        else
        {
            char wybor = menuInterfejs.wyborZMenuZalogowanegoUzytkownika();
            switch (wybor)
            {
            case '1':
                adresMenadzer.dodajAdresata();
                cout<< 1 << endl; //idOstatniegoAdresata = dodajAdresata(adresaci, idZalogowanegoUzytkownika, idOstatniegoAdresata);
                break;
            case '2':
                adresMenadzer.wyszukajAdresatowPoImieniu();
                break;
            case '3':
                cout<< 3 << endl; //wyszukajAdresatowPoNazwisku(adresaci);
                break;
            case '4':
                adresMenadzer.wyswietlWszystkichAdresatow();
                break;
            case '5':
                cout<< 5 << endl; /*
                idUsunietegoAdresata = usunAdresata(adresaci);
                idOstatniegoAdresata = podajIdOstatniegoAdresataPoUsunieciuWybranegoAdresata(idUsunietegoAdresata, idOstatniegoAdresata);
                */
                break;
            case '6':
                cout<< 6 << endl;
                //edytujAdresata(adresaci);
                break;
            case '7':
                 uzytkownikMenadzer.zmianaHaslaZalogowanegoUzytkownika();
                break;
            case '8':
                uzytkownikMenadzer.wyloguj();
                }
        }
    }
}
