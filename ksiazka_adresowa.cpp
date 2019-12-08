#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include "ksiazka_adresowa.h"

using namespace std;

///////////     POMOCNICZE        ///////////

string insertNewPassword(){
    string newUserPassword, newUserConfirmPassword;
    while (true){
        cout << "Podaj nowe haslo: ";
        cin >> newUserPassword;
        cout << "Potwierdz nowe haslo ponowanie: ";
        cin >> newUserConfirmPassword;
        if (newUserConfirmPassword == newUserPassword){
                return newUserPassword;
        }
        else {
            cout << "Wprowadzono 2 rozne hasla - sprobuj ponownie. " << endl;
        }
    }
}

void renameFile(){
    remove("Adresaci.txt");
    fstream oldFile;
    fstream newFile;
    oldFile.open("Adresaci_tymczasowy.txt", ios::in);
    newFile.open("Adresaci.txt", ios::out);
    string lineToTransfer;
    while (getline(oldFile, lineToTransfer)){
        newFile << lineToTransfer << endl;
    }
    oldFile.close();
    newFile.close();
    remove("Adresaci_tymczasowy.txt");
}

void dispalyEditContactMenuOptions(){
    cout << "Wybierz dana do edycji: " << endl;
    cout << "--------------------------------" << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - adres" << endl;
    cout << "4 - email" << endl;
    cout << "5 - numer telefonu" << endl;
    cout << "6 - powrot z menu" << endl;

}

string changeLettersToLower(string textToChange){
    if (!textToChange.empty())
    {
        transform(textToChange.begin(), textToChange.end(), textToChange.begin(), ::tolower);
    }
    return textToChange;
}

string changeFirstLetterToCapitalAndRestToLower(string textToChange){
    if (!textToChange.empty())
    {
        transform(textToChange.begin(), textToChange.end(), textToChange.begin(), ::tolower);
        textToChange[0] = toupper(textToChange[0]);
    }
    return textToChange;
}

int convertStringToInt(string liczbaDoKonwersji){
    int number = atoi(liczbaDoKonwersji.c_str());
    return number;
}

int AllContacts::returnHeighestId(){
    return heighestIdNumber;
}

User changeLineToUser(string inputLine){
    string temporaryWord, login, password;
    int lengthOfWord, id;
    for (int i = 0; i < 3; i ++){
        lengthOfWord = inputLine.find('|');
        temporaryWord = inputLine.substr(0, lengthOfWord);
        switch (i){
            case 0:{
                id = convertStringToInt(temporaryWord);
            }
            break;
            case 1:{
                login = temporaryWord;
            }
            break;
            case 2:{
                password = temporaryWord;
            }
            break;
        }
        inputLine.replace(0, lengthOfWord + 1, "");
    }
    User temUser(id, login, password);
    return temUser;

}

Contact changeLineToContact(string inputLine){
    string temporaryWord, name, surname, adres, email, phone;
    int lengthOfWord, idNumber, ownerId;
    for (int i = 0; i < 7; i++){
        lengthOfWord = inputLine.find('|');
        temporaryWord = inputLine.substr(0, lengthOfWord);
        switch (i){
            case 0: idNumber = convertStringToInt(temporaryWord);
            break;
            case 1: ownerId = convertStringToInt(temporaryWord);
            break;
            case 2: name = temporaryWord;
            break;
            case 3: surname = temporaryWord;
            break;
            case 4: adres = temporaryWord;
            break;
            case 5: email = temporaryWord;
            break;
            case 6: phone = temporaryWord;
            break;
        }
        inputLine.replace(0, lengthOfWord + 1, "");
    }
    Contact tempCont(idNumber, ownerId, name, surname, adres, email, phone);
    return tempCont;
}

string checkPasswordWithVerification(){
    string newUserPassword, newUserConfirmPassword;
    while (true){
        cout << "Podaj haslo: ";
        cin >> newUserPassword;
        cout << "Potwierdz haslo wprowadzajace je ponownie: ";
        cin >> newUserConfirmPassword;
        if (newUserConfirmPassword == newUserPassword){
                return newUserPassword;
        }
        else {
            cout << "Wprowadzono 2 rozne hasla - sprobuj ponownie. " << endl;
        }
    }
}

///////////     ALLUSERS CLASS       ///////////

void AllUsers::changePassword(int signedInUserId){
    for (int i = 0; i < listOfUsers.size(); i++){
        if (listOfUsers[i].returnId() == signedInUserId){
            string newPassword = insertNewPassword();
            listOfUsers[i].assignNewPassword(newPassword);
            break;
        }
    }
    cout << "Zmieniono haslo" << endl;
    saveUserDataToFile();
    Sleep(1500);
}

bool AllUsers::isLoginUsedByOtherUser(string newUserLogin){
    bool sameLoginExist = false;
    for (int i = 0; i < listOfUsers.size(); i++){
        if (listOfUsers[i].returnLogin()== newUserLogin){
            sameLoginExist = true;
            cout << "Wprowadzony login jest juz uzywany." << endl;
        }
    }
    return sameLoginExist;
}

string AllUsers::checkAndReturnCorrectLogin(){
    string newUserLogin;
    do{
        cout << "Podaj login: ";
        cin >> newUserLogin;
    }while (isLoginUsedByOtherUser(newUserLogin));
    return newUserLogin;
}

void AllUsers::saveUserDataToFile(){
    fstream fileOfUsers;
    fileOfUsers.open("Uzytkownicy.txt", ios::out);
    for (int i = 0; i < listOfUsers.size(); i++){
        fileOfUsers << listOfUsers[i].returnId() << "|" << listOfUsers[i].returnLogin() << "|" << listOfUsers[i].returnPassword() << "|" << endl;
    }
    cout << "Baza uzytkownikow zostala zaktualizowana" << endl;
    fileOfUsers.close();
}

bool AllUsers::enterPasswordToAccount(User userToLog){
    string password;
    for (int i = 3; i != 0; i--){
        cout << "Podaj haslo: ";
        cin >> password;
        if (password == userToLog.returnPassword()){
                cout << "Pomyslnie zalogowano do konta";
                return true;
        }
        else {
            cout << "Podano bledne haslo. Pozostalo " << i - 1 << " prob logowania" << endl;
            Sleep(1000);
        }
    }
    cout << "Przekroczono dopuszczalna liczbe prob logowania. Logowanie nie powiodlo sie!" << endl;
    return false;
}

int AllUsers::logUserToProgram(){
    if (listOfUsers.size() == 0){
        cout << "Brak uzytkownikow w liscie" << endl;
        return 0;
    }
    else {
    string login;
    cout << "Podaj login: ";
    cin >> login;
    for (int i = 0; i < listOfUsers.size(); i++){
        if (login == listOfUsers[i].returnLogin()){
            if (enterPasswordToAccount(listOfUsers[i])) return listOfUsers[i].returnId();
            else return 0;
        }
    }
    cout << "Nie znaleziono loginu na liscie" << endl;
    return 0;
    }
}

void AllUsers::registerUser(){
    int newUserId;
    string newUserLogin, newUserPassword;
    if (listOfUsers.size() == 0) newUserId = 1;
    else newUserId = lastUserId + 1;
    string login = checkAndReturnCorrectLogin();
    string password = checkPasswordWithVerification();
    User newUser(newUserId, login, password);
    listOfUsers.push_back(newUser);
    cout << "Dodano uzytkownika do programu" << endl;
    lastUserId = newUser.returnId();
    saveUserDataToFile();
}

void AllUsers::readUserDataFromFile(){
    fstream fileOfUsersData;
    string inputLine;
    fileOfUsersData.open("Uzytkownicy.txt", ios::in);
    if (fileOfUsersData.good() == true){
        while (getline(fileOfUsersData, inputLine)){
            User temporaryUser = changeLineToUser(inputLine);
            lastUserId = temporaryUser.returnId();
            listOfUsers.push_back(temporaryUser);
        }
    }
    fileOfUsersData.close();
}

AllUsers::AllUsers(){
    this -> readUserDataFromFile();
}

///////////     USER CLASS       ///////////
void User::assignNewPassword(string newPass){
    password = newPass;
}

User::User(int userId, string userLogin, string userPassword){
    idNumber = userId;
    login = userLogin;
    password = userPassword;
}

string User::returnLogin(){
    return login;
}

string User::returnPassword(){
    return password;
}

int User::returnId(){
    return idNumber;
}

///////////     CONTACT CLASS       ///////////

void Contact::display(){
    cout << idNumber << endl;
    cout << name << endl;
    cout << surname << endl;
    cout << address << endl;
    cout << email << endl;
    cout << phoneNumber << endl;
}

void Contact::addContactToMainFile(){
    fstream fileOfDataBase;
    fileOfDataBase.open("Adresaci.txt", ios::out | ios::app);
    fileOfDataBase << idNumber << "|" << ownerId << "|";
    fileOfDataBase << name << "|" << surname << "|";
    fileOfDataBase << address << "|" << email<< "|";
    fileOfDataBase << phoneNumber << "|" << endl;
    fileOfDataBase.close();
}

string Contact::returnPhone(){
    return phoneNumber;
}

string Contact::returnEmail(){
    return email;
}

string Contact::returnAdres(){
    return address;
}

string Contact::returnSurname(){
    return surname;
}

string Contact::returnName(){
    return name;
}

int Contact::returnId(){
    return idNumber;
}

int Contact::returnOwnerId(){
    return ownerId;
}

Contact::Contact(int id, int idOwner, string contactName, string contactSurname, string contactAddress, string contactEmail, string contactPhone){
    idNumber = id;
    ownerId = idOwner;
    name = contactName;
    surname = contactSurname;
    address = contactAddress;
    email = contactEmail;
    phoneNumber = contactPhone;
}

///////////     ALLCONTACTS CLASS       ///////////

void AllContacts::changePasswordForUser(){
    AllUsers allUsers;
    allUsers.changePassword(logedUserId);
}

void AllContacts::saveEditedContact(Contact editedContact){
    fstream originalFileOfContacts;
    originalFileOfContacts.open("Adresaci.txt", ios::in);
    if (originalFileOfContacts.good() != true){
        cout << "Nie istnieje plik z adresatami" << endl;
        exit(0);
    }
    fstream temporaryFile;
    temporaryFile.open("Adresaci_tymczasowy.txt", ios::out);
    string lineFromOriginalFile;
    while(getline(originalFileOfContacts, lineFromOriginalFile)){
        Contact contact = changeLineToContact(lineFromOriginalFile);
        if (contact.returnId() != editedContact.returnId()){
            temporaryFile << contact.returnId() << "|" << contact.returnOwnerId() << "|" << contact.returnName() << "|" << contact.returnSurname() << "|";
            temporaryFile << contact.returnAdres() << "|" << contact.returnEmail()<< "|" << contact.returnPhone() << "|" << endl;
            }
        else{
            temporaryFile << editedContact.returnId() << "|" << editedContact.returnOwnerId() << "|" << editedContact.returnName() << "|" << editedContact.returnSurname() << "|";
            temporaryFile << editedContact.returnAdres() << "|" << editedContact.returnEmail()<< "|" << editedContact.returnPhone() << "|" << endl;
            }
            }
    temporaryFile.close();
    originalFileOfContacts.close();
    renameFile();
}

Contact AllContacts::editSingleContact(Contact contactToEdit, int chosenOption){
    string dataToInsert, name, surname, adres, email, phone;
    int idNumber, ownerId;
    cout << "Edytuj wybrane dane: ";
    cin.sync();
    getline(cin, dataToInsert);
    name = contactToEdit.returnName();
    surname = contactToEdit.returnSurname();
    adres = contactToEdit.returnAdres();
    email = contactToEdit.returnEmail();
    phone = contactToEdit.returnPhone();
    idNumber = contactToEdit.returnId();
    ownerId = contactToEdit.returnOwnerId();
    switch (chosenOption){
        case 1: name = dataToInsert;
        break;
        case 2: surname = dataToInsert;
        break;
        case 3: adres = dataToInsert;
        break;
        case 4:email = dataToInsert;
        break;
        case 5: phone = dataToInsert;
        break;
    }
    Contact newContact(idNumber, ownerId, name, surname, adres, email, phone);
    return newContact;
}

void AllContacts::editContact(){
    cout << "Podaj id kontaktu do edycji: ";
    int numberIdToEdition;
    cin >> numberIdToEdition;
    int editionOption;
    dispalyEditContactMenuOptions();
    cin >> editionOption;
    if (editionOption >= 1 && editionOption <= 5){
        for (int i = 0; i < listOfContacts.size(); i++){
            if ( logedUserId == listOfContacts[i].returnOwnerId() && listOfContacts[i].returnId()== numberIdToEdition){
                listOfContacts[i] = editSingleContact(listOfContacts[i], editionOption);
                saveEditedContact(listOfContacts[i]);
                cout << "Edytowano kontakt" << endl;
                Sleep(1500);
            }
        }
    }
}

void AllContacts::saveDeletedContact(int numberIdOfEditedContact){
    fstream originalFileOfContacts;
    originalFileOfContacts.open("Adresaci.txt", ios::in);
    if (originalFileOfContacts.good() != true){
        cout << "Nie istnieje plik z adresatami" << endl;
        exit(0);
    }
    fstream temporaryFile;
    temporaryFile.open("Adresaci_tymczasowy.txt", ios::out);
    string lineFromOriginalFile, name, surname, adres, email, phone;
    int idNumber, ownerId;
    while(getline(originalFileOfContacts, lineFromOriginalFile)){
        Contact contact = changeLineToContact(lineFromOriginalFile);
        idNumber = contact.returnId();
        ownerId = contact.returnOwnerId();
        name = contact.returnName();
        surname = contact.returnSurname();
        adres = contact.returnAdres();
        email = contact.returnEmail();
        phone = contact.returnPhone();
        if (contact.returnId() != numberIdOfEditedContact){
            temporaryFile << contact.returnId() << "|" << contact.returnOwnerId() << "|";
            temporaryFile << contact.returnName() << "|" << contact.returnSurname() << "|";
            temporaryFile << contact.returnAdres() << "|" << contact.returnEmail() << "|";
            temporaryFile << contact.returnPhone() << "|" << endl;
            }
        }
    temporaryFile.close();
    originalFileOfContacts.close();
    renameFile();
}

void AllContacts::deleteContact(){
    int idToDelete;
    bool contactsIsUserContact = false;
    cout << "Podaj id uzytkownika do usuniecia: ";
    cin >> idToDelete;
    for (int i = 0; i < listOfContacts.size(); i++){
        if (listOfContacts[i].returnId() == idToDelete){
            listOfContacts.erase(listOfContacts.begin() + i);
            contactsIsUserContact = true;
        }
    }
    if (contactsIsUserContact){
        cout << "Usunieto kontakt!" << endl;
        saveDeletedContact(idToDelete);

    }
    else{
        cout << "Brak wskazanego kontaktu!" << endl;
    }
    Sleep(1500);
}

int AllContacts::logOut(){
    system("cls");
    return 0;
}

void AllContacts::findContactByName(){
    cout << "Podaj szukane imie: ";
    string nameOfContact;
    cin >> nameOfContact;
    for (int i = 0; i < listOfContacts.size(); i++){
        if (listOfContacts[i].returnName() == nameOfContact){
            listOfContacts[i].display();
            cout << endl;
        }
    }
    system("pause");
}

void AllContacts::findContactBySurname(){
    cout << "Podaj szukane nazwisko: ";
    string surnameOfContact;
    cin >> surnameOfContact;
    for (int i = 0; i < listOfContacts.size(); i++){
        if (listOfContacts[i].returnSurname() == surnameOfContact){
            listOfContacts[i].display();
            cout << endl;
        }
    }
    system("pause");
}

void AllContacts::displayAllContacts(){
    for (int i = 0; i < listOfContacts.size(); i++){
        listOfContacts[i].display();
        cout << endl;
    }
    system("pause");
}

void AllContacts::assignHeighestId(int idToAssign){
    heighestIdNumber = idToAssign;
}

void AllContacts::loadContacts(){
    fstream fileOfUsersData;
    string inputLine;
    fileOfUsersData.open("Adresaci.txt", ios::in);
    if (fileOfUsersData.good() == true){
            while (getline(fileOfUsersData, inputLine)){
                Contact temporaryContact = changeLineToContact(inputLine);
                int contactId = temporaryContact.returnId();
                ///
                if (contactId > returnHeighestId()) assignHeighestId(contactId);
                if (temporaryContact.returnOwnerId() == logedUserId){
                    listOfContacts.push_back(temporaryContact);
                }
        }
    }
    fileOfUsersData.close();
}

Contact AllContacts::getDataForNewUser(){
    string nameInput, surnameInput, addressInput, emailInput, phoneInput;
    cin.sync();
    cout << "Podaj imie: ";
    getline(cin, nameInput);
    cout << "Podaj nazwisko: ";
    getline(cin, surnameInput);
    cout << "Podaj adres: ";
    getline(cin,addressInput);
    cout << "Podaj email: ";
    getline(cin, emailInput);
    cout << "Podaj numer telefonu: ";
    getline(cin, phoneInput);
    string name = changeFirstLetterToCapitalAndRestToLower(nameInput);
    string surname = changeFirstLetterToCapitalAndRestToLower(surnameInput);
    string adres = changeFirstLetterToCapitalAndRestToLower(addressInput);
    string email = changeLettersToLower(emailInput);
    string phone = changeFirstLetterToCapitalAndRestToLower(phoneInput);
    int idNumber = returnHeighestId() + 1;
    int ownerId = logedUserId;
    Contact tempContact(idNumber, ownerId, name, surname, adres, email, phone);
    return tempContact;
}

void AllContacts::addContact(){
    Contact contactToAdd = getDataForNewUser();
    listOfContacts.push_back(contactToAdd);
    contactToAdd.addContactToMainFile();
    cout << "Dodano pomyslnie kontakt do bazy" << endl;
    Sleep(1500);
}

AllContacts::AllContacts(int id){
    logedUserId = id;
    heighestIdNumber = 0;
    this -> loadContacts();
}
