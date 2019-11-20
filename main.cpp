#include <iostream>
#include <iostream>
#include <fstream>
#include <windows.h>
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

int convertStringToInt(string liczbaDoKonwersji)
{
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

int startMenu(){
    while (true){
        cout << "Witaj w programie \"Ksiazka adresowa\" " << endl;
        cout << "________________________________" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cout << "Wybierz opcje z menu i wcisnij enter: ";
        vector <UserOfProgram> usersDatabase = readUsersDataFromFile();
        int userMenuOption;
        cin >> userMenuOption;
        int signedInUserId;
        switch (userMenuOption){
            case 1:
                signedInUserId = logUserToProgram(usersDatabase);
            break;
            case 2: {
                usersDatabase = registerUserToProgram(usersDatabase);
                saveUserDataToFile(usersDatabase);
            }
            break;
            case 3: exit(0);
        }
    Sleep(2500);
    system("cls");
    if (signedInUserId != 0) return signedInUserId;
    }
}

bool isContactAssignToUser(Contact userContact, int signedUserId){
    if (signedUserId == userContact.contactOwnerId){
        return true;
    }
    else return false;
}

///////////////////ADDRESS BOOK PART BELOW ////////////////////////////

Contact convertLineToContactStructure(string lineOfData){
    Contact temporaryContact;
    string temporaryWord;
    int lengthOfWord;
    for (int i = 0; i < 7; i++){
        lengthOfWord = lineOfData.find('|');
        temporaryWord = lineOfData.substr(0, lengthOfWord);
        switch (i){
            case 0: temporaryContact.contactId = convertStringToInt(temporaryWord);
            break;
            case 1: temporaryContact.contactOwnerId = convertStringToInt(temporaryWord);
            break;
            case 2: temporaryContact.name = temporaryWord;
            break;
            case 3: temporaryContact.surname = temporaryWord;
            break;
            case 4: temporaryContact.adres = temporaryWord;
            break;
            case 5: temporaryContact.email = temporaryWord;
            break;
            case 6: temporaryContact.phoneNumber = temporaryWord;
            break;
        }
        lineOfData.replace(0, lengthOfWord + 1, "");
    }
    return temporaryContact;
}

vector <Contact> readUsersDataFromFile(int signedUserId){
    vector<Contact> listOfUserContacts(0);
    fstream fileOfAllContacts;
    Contact temporaryContact;
    string inputLine;
    fileOfAllContacts.open("Adresaci.txt", ios::in);
    if (fileOfAllContacts.good() == true){
        while (getline(fileOfAllContacts, inputLine)){
            temporaryContact = convertLineToContactStructure(inputLine);
            if (isContactAssignToUser){
                listOfUserContacts.push_back(temporaryContact);
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

vector <Contact> addContactToDataBase(vector<Contact> listOfAllContacts, int signedUserId){
    Contact temporaryContact;
    int lastContactOnTheListId;
    if (listOfAllContacts.empty()){
        lastContactOnTheListId = 0;
    }
    else{
        lastContactOnTheListId = listOfAllContacts[listOfAllContacts.size() - 1].contactId;
    }
    int idNumber = lastContactOnTheListId + 1;
    temporaryContact.contactId = idNumber;
    temporaryContact.contactOwnerId = signedUserId;
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

    // w tym miejscu bedzie plik lokalny nadpisywany
    //addContactToTextFileOfDataBase(temporaryContact);
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

vector <Contact> deleteContact(vector<Contact> listOfAllContacts){
    int idToDelete;
    cout << "Podaj id uzytkownika do usuniecia: ";
    cin >> idToDelete;
    for (int i = 0; i < listOfAllContacts.size(); i++){
        if (listOfAllContacts[i].contactId == idToDelete){
            listOfAllContacts.erase(listOfAllContacts.begin() + i);
        }
    }
    system("pause");
    return listOfAllContacts;
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
    }
    return listOfAllContacts;
}

void changePasswordForUser(int signedInUserId){
    vector<UserOfProgram> allUsers = readUsersDataFromFile();
    for (int i = 0; i < allUsers.size(); i++){
        if (allUsers[i].userId == signedInUserId){
            string newPassword = checkPasswordWithVerification();
            allUsers[i].userPassword = newPassword;
            break;
        }
    }
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
        case 6: listOfUserContacts = editContactMenu(listOfUserContacts);
        break;
        case 7: changePasswordForUser(signedUserId);
        break;
        case 8: return 0;
        break;
        case 9: exit(0);
        break;
        }
    }
    Sleep(1500);
    system("cls");
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
