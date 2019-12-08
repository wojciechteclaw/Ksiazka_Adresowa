#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include "ksiazka_adresowa.h"

using namespace std;

void displayStartMentu(){
    cout << "Witaj w programie \"Ksiazka adresowa\" " << endl;
    cout << "________________________________" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zamknij program" << endl;
    cout << "Wybierz opcje z menu i wcisnij enter: ";
}

void displaySignedInUserMenu(){
    cout << "Wybierz opcje z menu" << endl;
    cout << "-----------------------------" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;
    cout << "9. Zakoncz program" << endl;
}

int menuForSignedInUser(int signedUserId){
    int userChoiceOfOptionFromMenu;
    AllContacts allContacts(signedUserId);
    while (true){
        displaySignedInUserMenu();
        cin >> userChoiceOfOptionFromMenu;
        switch (userChoiceOfOptionFromMenu){
        case 1: allContacts.addContact();
        break;
        case 2: allContacts.findContactByName();
        break;
        case 3: allContacts.findContactBySurname();
        break;
        case 4: allContacts.displayAllContacts();
        break;
        case 5: allContacts.deleteContact();
        break;
        case 6: allContacts.editContact();
        break;
        case 7: allContacts.changePasswordForUser();
        break;
        case 8: return allContacts.logOut();
        break;
        case 9: exit(0);
        break;
        }
        system("cls");
    }
}

int startMenu(){
    AllUsers allUsers;
    while (true){
        displayStartMentu();
        int userMenuOption, signedInUserId;
        cin >> userMenuOption;
        switch (userMenuOption){
            case 1: signedInUserId = allUsers.logUserToProgram();
            break;
            case 2: { allUsers.registerUser();
            }
            break;
            case 3: exit(0);
        }
    Sleep(1500);
    system("cls");
    if (signedInUserId != 0) return signedInUserId;
    }
}

int main(){
    int logedUserId = 0;
    while (true){
        while (logedUserId == 0){
            logedUserId = startMenu();
        }
        logedUserId = menuForSignedInUser(logedUserId);
    }
}
