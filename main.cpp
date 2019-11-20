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
        int lastUserId = usersList[usersList.size() - 1].userId;
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
    }
}

int main()
{
    int logedUserId;
    while (true){
        logedUserId = startMenu();
    }

}
