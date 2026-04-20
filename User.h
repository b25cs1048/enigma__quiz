#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
private:
    string hashPassword(string password);
    bool userExists(string username);
    bool adminExists(string a_name);
    string getHiddenPassword();

public:
    void registerUser();
    bool loginUser(string& loggedInUser);
    bool adminLogin();
    void change_passw_user();
    bool adminRegister();
    bool adminLogin(string& adminName);
};

#endif