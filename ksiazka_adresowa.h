#include <iostream>

using namespace std;

class Contact;
class User;

 class AllUsers{
     vector <User> listOfUsers;
     int maxUserId();
     void readUserDataFromFile();
     int lastUserId;
     bool enterPasswordToAccount(User);
     void saveUserDataToFile();
     bool isLoginUsedByOtherUser(string);
     string checkAndReturnCorrectLogin();

 public:
     AllUsers();
     void registerUserToProgram();
     int logUserToProgram();
     void registerUser();
     void changePassword(int);

 };

class User{
    int idNumber;
    string login;
    string password;

public:
    User(int, string, string);
    string returnLogin();
    string returnPassword();
    int returnId();
    void assignNewPassword(string);
};

class AllContacts{
    int logedUserId;
    Contact editSingleContact(Contact, int);
    vector <Contact> listOfContacts;
    void loadContacts();
    int heighestIdNumber;
    void assignHeighestId(int);
    Contact getDataForNewUser();
    void returnUserId();
    int returnHeighestId();
    void saveEditedContact(Contact);
    void saveDeletedContact(int);

public:
    AllContacts(int);
    void addContact();
    void displayAllContacts();
    void findContactByName();
    void findContactBySurname();
    void deleteContact();
    void editContact();
    void changePasswordForUser();
    int logOut();

};

class Contact{
    int idNumber;
    int ownerId;
    string name;
    string surname;
    string address;
    string email;
    string phoneNumber;

public:
    Contact(int, int, string, string, string, string, string);
    int returnId();
    void addContactToMainFile();
    void display();
    int returnOwnerId();
    string returnName();
    string returnSurname();
    string returnAdres();
    string returnEmail();
    string returnPhone();
};
