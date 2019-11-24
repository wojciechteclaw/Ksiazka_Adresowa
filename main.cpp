#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <vector>

using namespace std;

struct Contact{
    int contactId;
    int contactOwnerId;
    string name, surname, adres, email, phoneNumber;
};

struct UserOfProgram{
    int userId;
    string userLogin;
    string userPassword;
};

int convertStringToInt(string liczbaDoKonwersji){
    int number = atoi(liczbaDoKonwersji.c_str());
    return number;
}

bool enterPasswordToAccount(UserOfProgram userToLog){
    string password;
    for (int i = 3; i != 0; i--){
        cout << "Podaj haslo: ";
        cin >> password;
        if (password == userToLog.userPassword){
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

int logUserToProgram(vector <UserOfProgram> usersList){
    if (usersList.size() == 0){
        cout << "Brak uzytkownikow w liscie" << endl;
        return 0;
    }
    else {
    string login;
    cout << "Podaj login: ";
    cin >> login;
    for (int i = 0; i < usersList.size(); i++){
        if (login == usersList[i].userLogin){
            if (enterPasswordToAccount(usersList[i])) return usersList[i].userId;
            else return 0;
        }
    }
    cout << "Nie znaleziono loginu na liscie" << endl;
    return 0;
    }
}

bool isLoginUsedByOtherUser(vector <UserOfProgram> usersList, string newUserLogin){
    bool sameLoginExist = false;
    for (int i = 0; i < usersList.size(); i++){
        if (usersList[i].userLogin == newUserLogin){
            sameLoginExist = true;
            cout << "Wprowadzony login jest juz uzywany." << endl;
        }
    }
    return sameLoginExist;
}

string checkAndReturnCorrectLogin(vector <UserOfProgram> usersList){
    string newUserLogin;
    do{
        cout << "Podaj login: ";
        cin >> newUserLogin;
    }while (isLoginUsedByOtherUser(usersList, newUserLogin));
    return newUserLogin;
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

vector <UserOfProgram> registerUserToProgram(vector <UserOfProgram> usersList){
    UserOfProgram newUser;
    int newUserId;
    string newUserLogin, newUserPassword;
    if (usersList.size() == 0){
        newUserId = 1;
    }
    else {
        int lastUserListIndex = usersList.size() - 1;
        int lastUserId = usersList[lastUserListIndex].userId;
        newUserId = lastUserId + 1;
    }
    newUser.userId = newUserId;
    newUser.userLogin = checkAndReturnCorrectLogin(usersList);
    newUser.userPassword = checkPasswordWithVerification();
    usersList.push_back(newUser);
    cout << "Dodano uzytkownika do programu" << endl;
    return usersList;
}

void saveUserDataToFile(vector <UserOfProgram> usersList){
    fstream fileOfUsers;
    fileOfUsers.open("Uzytkownicy.txt", ios::out);
    for (int i = 0; i < usersList.size(); i++){
        fileOfUsers << usersList[i].userId << "|" << usersList[i].userLogin << "|" << usersList[i].userPassword << "|" << endl;
    }
    cout << "Baza uzytkownikow zostala zaktualizowana" << endl;
    fileOfUsers.close();
}

UserOfProgram changeLineToUserData(string inputLine){
    UserOfProgram userData;
    string temporaryWord;
    int lengthOfWord;
    for (int i = 0; i < 3; i ++){
        lengthOfWord = inputLine.find('|');
        temporaryWord = inputLine.substr(0, lengthOfWord);
        switch (i){
            case 0:{
                userData.userId = convertStringToInt(temporaryWord);
            }
            break;
            case 1:{
                userData.userLogin = temporaryWord;
            }
            break;
            case 2:{
                userData.userPassword = temporaryWord;
            }
            break;
        }
        inputLine.replace(0, lengthOfWord + 1, "");
    }
    return userData;
}

vector <UserOfProgram> readUsersDataFromFile(){
    vector <UserOfProgram> listOfUsers(0);
    fstream fileOfUsersData;
    UserOfProgram temporaryUser;
    string inputLine;
    fileOfUsersData.open("Uzytkownicy.txt", ios::in);
    if (fileOfUsersData.good() == true){
        while (getline(fileOfUsersData, inputLine)){
            temporaryUser = changeLineToUserData(inputLine);
            listOfUsers.push_back(temporaryUser);
        }
    }
    fileOfUsersData.close();
    return listOfUsers;
}

void displayStartMentu(){
    cout << "Witaj w programie \"Ksiazka adresowa\" " << endl;
    cout << "________________________________" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zamknij program" << endl;
    cout << "Wybierz opcje z menu i wcisnij enter: ";
}

int startMenu(){
    while (true){
        displayStartMentu();
        vector <UserOfProgram> usersDatabase = readUsersDataFromFile();
        int userMenuOption, signedInUserId;
        cin >> userMenuOption;
        switch (userMenuOption){
            case 1: signedInUserId = logUserToProgram(usersDatabase);
            break;
            case 2: {
                usersDatabase = registerUserToProgram(usersDatabase);
                saveUserDataToFile(usersDatabase);
            }
            break;
            case 3: exit(0);
        }
    Sleep(1500);
    system("cls");
    if (signedInUserId != 0) return signedInUserId;
    }
}

///////////////////ADDRESS BOOK PART BELOW ////////////////////////////

Contact convertLineToContactStructure(string lineOfData){
    Contact contact;
    string temporaryWord;
    int lengthOfWord;
    for (int i = 0; i < 7; i++){
        lengthOfWord = lineOfData.find('|');
        temporaryWord = lineOfData.substr(0, lengthOfWord);
        switch (i){
            case 0: contact.contactId = convertStringToInt(temporaryWord);
            break;
            case 1: contact.contactOwnerId = convertStringToInt(temporaryWord);
            break;
            case 2: contact.name = temporaryWord;
            break;
            case 3: contact.surname = temporaryWord;
            break;
            case 4: contact.adres = temporaryWord;
            break;
            case 5: contact.email = temporaryWord;
            break;
            case 6: contact.phoneNumber = temporaryWord;
            break;
        }
        lineOfData.replace(0, lengthOfWord + 1, "");
    }
    return contact;
}

vector <Contact> readUsersDataFromFile(int signedUserId){
    vector<Contact> listOfUserContacts(0);
    fstream fileOfAllContacts;
    Contact contact;
    string inputLine;
    fileOfAllContacts.open("Adresaci.txt", ios::in);
    if (fileOfAllContacts.good() == true){
        while (getline(fileOfAllContacts, inputLine)){
            contact = convertLineToContactStructure(inputLine);
            if (contact.contactOwnerId == signedUserId){
                listOfUserContacts.push_back(contact);
            }
        }
    }
    fileOfAllContacts.close();
    return listOfUserContacts;
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

void displaySingleContact(Contact contactToDisplay){
    cout << contactToDisplay.contactId<< endl;
    cout << contactToDisplay.name << endl;
    cout << contactToDisplay.surname << endl;
    cout << contactToDisplay.adres << endl;
    cout << contactToDisplay.email << endl;
    cout << contactToDisplay.phoneNumber << endl;
}

void addContactToMainFile(Contact contactToInsert){
    fstream fileOfDataBase;
    fileOfDataBase.open("Adresaci.txt", ios::out | ios::app);
    fileOfDataBase << contactToInsert.contactId << "|" << contactToInsert.contactOwnerId << "|";
    fileOfDataBase << contactToInsert.name << "|" << contactToInsert.surname << "|";
    fileOfDataBase << contactToInsert.adres << "|" << contactToInsert.email<< "|";
    fileOfDataBase << contactToInsert.phoneNumber << "|" << endl;
    fileOfDataBase.close();
}

int maxUsedId(){
    int maxNumber = 0;
    fstream fileOfAllContacts;
    Contact contact;
    string inputLine;
    fileOfAllContacts.open("Adresaci.txt", ios::in);
    if (fileOfAllContacts.good() == true){
        while (getline(fileOfAllContacts, inputLine)){
            contact = convertLineToContactStructure(inputLine);
            if (contact.contactId > maxNumber){
                maxNumber = contact.contactId;
            }
        }
    }
    fileOfAllContacts.close();
    return maxNumber;
}

Contact getDataForNewUser(){
    Contact contact;
    cin.sync();
    cout << "Podaj imie: ";
    getline(cin, contact.name);
    cout << "Podaj nazwisko: ";
    getline(cin, contact.surname);
    cout << "Podaj adres: ";
    getline(cin,contact.adres);
    cout << "Podaj email: ";
    getline(cin, contact.email);
    cout << "Podaj numer telefonu: ";
    getline(cin, contact.phoneNumber);
    return contact;
}

vector <Contact> addContactToDataBase(vector<Contact> listOfAllContacts, int signedUserId){
    int lastContactOnTheListId;
    lastContactOnTheListId = maxUsedId();

    int idNumber = lastContactOnTheListId + 1;
    Contact contact = getDataForNewUser();
    contact.contactId = idNumber;
    contact.contactOwnerId = signedUserId;

    listOfAllContacts.push_back(contact);
    addContactToMainFile(contact);
    cout << "Dodano pomyslnie kontakt do bazy" << endl;
    return listOfAllContacts;
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

void saveDeletedContact(int numberIdOfEditedContact){
    fstream originalFileOfContacts;
    originalFileOfContacts.open("Adresaci.txt", ios::in);
    if (originalFileOfContacts.good() != true){
        cout << "Nie istnieje plik z adresatami" << endl;
        exit(0);
    }
    fstream temporaryFile;
    temporaryFile.open("Adresaci_tymczasowy.txt", ios::out);
    string lineFromOriginalFile;
    Contact contact;
    while(getline(originalFileOfContacts, lineFromOriginalFile)){
        contact = convertLineToContactStructure(lineFromOriginalFile);
        if (contact.contactId != numberIdOfEditedContact){
            temporaryFile << contact.contactId << "|" << contact.contactOwnerId << "|";
            temporaryFile << contact.name << "|" << contact.surname << "|";
            temporaryFile << contact.adres << "|" << contact.email<< "|";
            temporaryFile << contact.phoneNumber << "|" << endl;
            }
        }
    temporaryFile.close();
    originalFileOfContacts.close();
    renameFile();
}

vector <Contact> deleteContact(vector<Contact> listOfAllContacts){
    int idToDelete;
    bool contactsIsUserContact = false;
    cout << "Podaj id uzytkownika do usuniecia: ";
    cin >> idToDelete;
    for (int i = 0; i < listOfAllContacts.size(); i++){
        if (listOfAllContacts[i].contactId == idToDelete){
            listOfAllContacts.erase(listOfAllContacts.begin() + i);
            contactsIsUserContact = true;
        }
    }
    if (contactsIsUserContact){
        cout << "Usunieto kontakt!" << endl;
        saveDeletedContact( idToDelete);
    }
    else {
        cout << "Brak wskazanego kontaktu!" << endl;
    }
    return listOfAllContacts;
}

void saveToTemporaryFile(fstream fileName, Contact contactToSave){
    fileName << contactToSave.contactId << "|" << contactToSave.contactOwnerId << "|";
    fileName << contactToSave.name << "|" << contactToSave.surname << "|";
    fileName << contactToSave.adres << "|" << contactToSave.email<< "|";
    fileName << contactToSave.phoneNumber << "|" << endl;

}

void saveEditedContact(Contact editedContact){
    fstream originalFileOfContacts;
    originalFileOfContacts.open("Adresaci.txt", ios::in);
    if (originalFileOfContacts.good() != true){
        cout << "Nie istnieje plik z adresatami" << endl;
        exit(0);
    }
    fstream temporaryFile;
    temporaryFile.open("Adresaci_tymczasowy.txt", ios::out);
    string lineFromOriginalFile;
    Contact contact;
    while(getline(originalFileOfContacts, lineFromOriginalFile)){
        contact = convertLineToContactStructure(lineFromOriginalFile);
        if (contact.contactId != editedContact.contactId){
            temporaryFile << contact.contactId << "|" << contact.contactOwnerId << "|" << contact.name << "|" << contact.surname << "|";
            temporaryFile << contact.adres << "|" << contact.email<< "|" << contact.phoneNumber << "|" << endl;
            }
        else{
            temporaryFile << editedContact.contactId << "|" << editedContact.contactOwnerId << "|" << editedContact.name << "|" << editedContact.surname << "|";
            temporaryFile << editedContact.adres << "|" << editedContact.email<< "|" << editedContact.phoneNumber << "|" << endl;
        }
        }
    temporaryFile.close();
    originalFileOfContacts.close();
    renameFile();
}

Contact editSingleContact(Contact contactToEdit, int chosenOption){
    string dataToInsert;
    cout << "Edytuj wybrane dane: ";
    cin.sync();
    getline(cin, dataToInsert);
    switch (chosenOption){
        case 1: contactToEdit.name = dataToInsert;
        break;
        case 2: contactToEdit.surname = dataToInsert;
        break;
        case 3:contactToEdit.adres = dataToInsert;
        break;
        case 4:contactToEdit.email = dataToInsert;
        break;
        case 5: contactToEdit.phoneNumber = dataToInsert;
        break;
    }
    return contactToEdit;
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

vector<Contact> editContactMenu(vector<Contact> listOfAllContacts, int signedUserId){
    cout << "Podaj id kontaktu do edycji: ";
    int numberIdToEdition;
    cin >> numberIdToEdition;
    int editionOption;
    dispalyEditContactMenuOptions();
    cin >> editionOption;
    if (editionOption >= 1 && editionOption <= 5){
        for (int i = 0; i < listOfAllContacts.size(); i++){
            if (signedUserId == listOfAllContacts[i].contactOwnerId && listOfAllContacts[i].contactId == numberIdToEdition){
                listOfAllContacts[i] = editSingleContact(listOfAllContacts[i], editionOption);
                saveEditedContact(listOfAllContacts[i]);
                cout << "Edytowano kontakt" << endl;
            }
        }
    }
    return listOfAllContacts;
}

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

void changePasswordForUser(int signedInUserId){
    vector<UserOfProgram> allUsers = readUsersDataFromFile();
    for (int i = 0; i < allUsers.size(); i++){
        if (allUsers[i].userId == signedInUserId){
            string newPassword = insertNewPassword();
            allUsers[i].userPassword = newPassword;
            break;
        }
    }
    cout << "Zmieniono haslo" << endl;
    saveUserDataToFile(allUsers);
}

int menuForSignedInUser(int signedUserId){
    vector <Contact> listOfUserContacts;
    int userChoiceOfOptionFromMenu;
    listOfUserContacts = readUsersDataFromFile(signedUserId);
    while (true){
        displaySignedInUserMenu();
        cin >> userChoiceOfOptionFromMenu;
        switch (userChoiceOfOptionFromMenu){
        case 1: listOfUserContacts = addContactToDataBase(listOfUserContacts, signedUserId);
        break;
        case 2: findContactByName(listOfUserContacts);
        break;
        case 3: findContactBySurname(listOfUserContacts);
        break;
        case 4: displayAllContacts(listOfUserContacts);
        break;
        case 5: listOfUserContacts = deleteContact(listOfUserContacts);
        break;
        case 6: listOfUserContacts = editContactMenu(listOfUserContacts, signedUserId);
        break;
        case 7: changePasswordForUser(signedUserId);
        break;
        case 8: return 0;
        break;
        case 9: exit(0);
        break;
        }
        Sleep(1500);
        system("cls");
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
