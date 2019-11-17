#include <iostream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;

struct Contact{
    int id;
    string name, surname, adres, email, phoneNumber;
};

string convertIntToString(int liczbaDoKonwersji)
{
    ostringstream ss;
    ss << liczbaDoKonwersji;
    return ss.str();
}

int convertStringToInt(string liczbaDoKonwersji)
{
    int number = atoi(liczbaDoKonwersji.c_str());
    return number;
}

Contact changeLineOfTextToContactStructure(string lineOfText){
    Contact temporaryContact;
    string temporaryWord;
    int lengthOfWord;
    for (int i = 0; i < 6; i++){
        lengthOfWord = lineOfText.find('|');
        temporaryWord = lineOfText.substr(0, lengthOfWord);
        switch (i){
        case 0:{
            temporaryContact.id = convertStringToInt(temporaryWord);
        }
        break;
        case 1:{
            temporaryContact.name = temporaryWord;
        }
        break;
        case 2:{
            temporaryContact.surname = temporaryWord;
        }
        break;
        case 3:{
            temporaryContact.adres = temporaryWord;
        }
        break;
        case 4:{
            temporaryContact.email = temporaryWord;
        }
        break;
        case 5:{
            temporaryContact.phoneNumber = temporaryWord;
        }
        break;
        }
        lineOfText.replace(0, lengthOfWord + 1, "");
    }
    return temporaryContact;
}

vector<Contact> readContactsFromFile(){
    vector<Contact> listOfContacts(0);
    fstream fileOfContacts;
    Contact temporaryContact;
    string line;
    fileOfContacts.open("databaseContact.txt", ios::in);
    if (fileOfContacts.good() == true){
        while (getline(fileOfContacts, line)){
                temporaryContact = changeLineOfTextToContactStructure(line);
                listOfContacts.push_back(temporaryContact);
        }
    }
    else{
        fileOfContacts.close();
    }
    return listOfContacts;
}

void addContactToTextFileOfDataBase(Contact contactToAdd){
    fstream fileOfContacts;
    fileOfContacts.open("databaseContact.txt",  ios::app);
    if (fileOfContacts.good() == true){
        fileOfContacts << contactToAdd.id << "|" << contactToAdd.name << "|" << contactToAdd.surname << "|";
        fileOfContacts << contactToAdd.adres << "|" << contactToAdd.email << "|" << contactToAdd.phoneNumber << "|" << endl;
        cout << "Kontakt zostal dodany pomysle do bazy" << endl;
        fileOfContacts.close();
    }
    else {
        cout << "Nie udalo sie dodac pliku" << endl;
    }
    fileOfContacts.close();
    system("pause");
}

vector<Contact> addContactToDataBase(vector<Contact> listOfAllContacts){
    Contact temporaryContact;
    int lastContactOnTheListId;
    if (listOfAllContacts.empty()){
        lastContactOnTheListId = 0;
    }
    else{
        lastContactOnTheListId = listOfAllContacts[listOfAllContacts.size() - 1].id;
    }
    int idNumber = lastContactOnTheListId + 1;
    temporaryContact.id = idNumber;
    cin.sync();
    cout << "Podaj imie: ";
    getline(cin, temporaryContact.name);
    cout << "Podaj nazwisko: ";
    getline(cin, temporaryContact.surname);
    cout << "Podaj adres: ";
    getline(cin,temporaryContact.adres);
    cout << "Podaj email: ";
    getline(cin, temporaryContact.email);
    cout << "Podaj numer telefonu: ";
    getline(cin, temporaryContact.phoneNumber);
    listOfAllContacts.push_back(temporaryContact);
    addContactToTextFileOfDataBase(temporaryContact);
    return listOfAllContacts;
}

void displaySingleContact(Contact contactToDisplay){
    cout << contactToDisplay.id << endl;
    cout << contactToDisplay.name << endl;
    cout << contactToDisplay.surname << endl;
    cout << contactToDisplay.adres << endl;
    cout << contactToDisplay.email << endl;
    cout << contactToDisplay.phoneNumber << endl;
}

void findContactByName(vector<Contact> listOfAllContacts){
    cout << "Podaj szukane imie: ";
    string nameOfContact;
    cin >> nameOfContact;
    for (int i = 0; i < listOfAllContacts.size(); i++){
        if (listOfAllContacts[i].name == nameOfContact){
            displaySingleContact(listOfAllContacts[i]);
            cout << endl;
        }
    }
    system("pause");
}

void findContactBySurname(vector<Contact> listOfAllContacts){
    cout << "Podaj szukane nazwisko: ";
    string surnameOfContact;
    cin >> surnameOfContact;
    for (int i = 0; i < listOfAllContacts.size(); i++){
        if (listOfAllContacts[i].surname == surnameOfContact){
            displaySingleContact(listOfAllContacts[i]);
            cout << endl;
        }
    }
    system("pause");
}

void displayAllContacts(vector<Contact> listOfAllContacts){
    for (vector<Contact>::iterator itr = listOfAllContacts.begin(); itr != listOfAllContacts.end(); ++itr){
        displaySingleContact(*itr);
        cout << endl;
    }
    system("pause");
}

void reSaveAllContacts(vector<Contact> listOfAllContacts){
    fstream fileOfContacts;
    fileOfContacts.open("databaseContact.txt",  ios::out);
    for (int i = 0; i < listOfAllContacts.size(); i++){
        fileOfContacts << listOfAllContacts[i].id << "|" << listOfAllContacts[i].name << "|" << listOfAllContacts[i].surname << "|";
        fileOfContacts << listOfAllContacts[i].adres << "|" << listOfAllContacts[i].email << "|" << listOfAllContacts[i].phoneNumber << "|" << endl;
    }
    cout << "Baza danych zostala zaaktualizowana" << endl;
    fileOfContacts.close();
}

vector<Contact> deleteContact(vector<Contact> listOfAllContacts){
    int idToDelete;
    cout << "Podaj id uzytkownika do usuniecia: ";
    cin >> idToDelete;
    for (int i = 0; i < listOfAllContacts.size(); i++){
        if (listOfAllContacts[i].id == idToDelete){
            listOfAllContacts.erase(listOfAllContacts.begin() + i);
        }
    }
    reSaveAllContacts(listOfAllContacts);
    system("pause");
    return listOfAllContacts;
}

Contact editSingleContact(Contact contactToEdit, int chosenOption){
    string dataToEdition;
    cout << "Edytuj wybrane dane: ";
    cin.sync();
    getline(cin, dataToEdition);
    switch (chosenOption){
        case 1:{
            contactToEdit.name = dataToEdition;
        }
        break;
        case 2:{
            contactToEdit.surname = dataToEdition;
        }
        break;
        case 3:{
            contactToEdit.adres = dataToEdition;
        }
        break;
        case 4:{
            contactToEdit.email = dataToEdition;
        }
        break;
        case 5:{
            contactToEdit.phoneNumber = dataToEdition;
        }
        break;
    }
    return contactToEdit;
}

vector<Contact> editContactMenu(vector<Contact> listOfAllContacts){
    cout << "Podaj id kontaktu do edycji: ";
    int numberIdToEdition;
    cin >> numberIdToEdition;
    cout << "Wybierz dana do edycji: " << endl;
    cout << "--------------------------------" << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - adres" << endl;
    cout << "4 - email" << endl;
    cout << "5 - numer telefonu" << endl;
    cout << "6 - powrot z menu" << endl;
    int editionOption;
    cin >> editionOption;
    if (editionOption >= 1 && editionOption <= 5){
        listOfAllContacts[numberIdToEdition - 1] = editSingleContact(listOfAllContacts[numberIdToEdition - 1], editionOption);
        reSaveAllContacts(listOfAllContacts);
    }
    system("pause");
    return listOfAllContacts;
}

int main()
{
    vector<Contact> listOfAllContacts;
    int userChoiceOfOptionFromMenu;
    listOfAllContacts = readContactsFromFile();
    while (true){
        cout << "Wybierz opcje z menu" << endl;
        cout << "-----------------------------" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << endl;
        cout << "Wprowadz opcje: ";
        cin >> userChoiceOfOptionFromMenu;

        switch (userChoiceOfOptionFromMenu){
            case 1: listOfAllContacts = addContactToDataBase(listOfAllContacts);
                break;
            case 2: findContactByName(listOfAllContacts);
                break;
            case 3: findContactBySurname(listOfAllContacts);
                break;
            case 4: displayAllContacts(listOfAllContacts);
                break;
            case 5: listOfAllContacts = deleteContact(listOfAllContacts);
                break;
            case 6: listOfAllContacts = editContactMenu(listOfAllContacts);
                break;
            case 9: exit(0);
                break;
        }
        system("cls");
    }
}
