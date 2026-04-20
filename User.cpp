#include "User.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <conio.h>


using namespace std ;

string RED   = "\033[31m";
string GREEN = "\033[32m";
string BLUE  = "\033[34m";
string RESET = "\033[0m";


string User::hashPassword(string password){
    hash <string> hasher ;
    return to_string(hasher(password)) ;
}



string User::getHiddenPassword() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) {
            break;
        }
        else if (ch == 8) {  
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";  
            }
        }
        else {
            password += ch;
            cout << "*"; 
        }
    }

    cout << endl;
    return password;
}


bool User::userExists(string user_name){ 
    ifstream file("users.txt") ;
    string u, p ;

    while(file >> u >> p)
    {
        if (u == user_name) return true ;
    }
    
    return false ;

}

bool User::adminExists(string a_name){ 
    ifstream file("admins.txt") ;
    string u, p ;

    while(file >> u >> p)
    {
        if (u == a_name) return true ;
    }
    
    return false ;

}


void User::registerUser(){
    string user_name, passw ;

    cout << BLUE <<"Enter new username : " << RESET;
    cin >> user_name ;

    if(userExists(user_name))
        {
        cout << RED <<"| Username already exists.. |\n"<< RESET ;
        return ;
        }

    cout << BLUE <<"Enter password : " << RESET;
    passw = getHiddenPassword();

    string hashed = hashPassword(passw) ;

    ofstream file("users.txt", ios::app);
    file << user_name <<" "<< hashed << endl ;

    cout << GREEN <<"| Registration successful.. |\n" <<RESET;
}


bool User::loginUser(string& loggedInUser){
    string user_name, passw;

    cout << BLUE <<"Enter username : "<< RESET ;
    cin >> user_name;
    cout << BLUE <<"Enter password : "<< RESET ;
    passw = getHiddenPassword();

    string hashedInput = hashPassword(passw) ;

    ifstream file("users.txt") ;
    string u, p ;

    while(file >> u >> p)
    {
        if (u == user_name && p == hashedInput) 
        {
            cout << GREEN <<"Login Successful\n"<<RESET ;
            loggedInUser = user_name ;
            return true ;
        }
    }

    cout << RED <<"| Invalid user username or password.. |\n" << RESET ;


    return false ;
}


// bool User::adminLogin(){  
//     string user_name, passw ;

//     cout <<"Enter Username: " ;
//     cin >> user_name ;
//     cout <<"Enter Password: " ;
//     passw = getHiddenPassword();

//     if(user_name == "admin" && passw == "admin123")
//     {
//         cout <<"admin login successful..\n" ;
//         return true ;
//     }

//     cout << RED <<" | Invalid admin username Or password.. |\n" << RESET;


//     return false ;
// }

void User::change_passw_user() {
    string u_name, oldPassw, newPassw;

    cout << BLUE <<" Enter Username : "<< RESET;
    cin >> u_name;

    cout << BLUE <<" Enter Old Password : "<< RESET;
    oldPassw = getHiddenPassword();

    ifstream file("users.txt");
    vector<pair<string, string>> users;

    string u, p;

    bool found = false;

    while (file >> u >> p) {
        if (u == u_name && p == hashPassword(oldPassw)) {
            found = true;

            cout << BLUE <<" Enter new password : "<< RESET;
            newPassw = getHiddenPassword();

            users.push_back({u, hashPassword(newPassw)});
        }
        else {
            users.push_back({u, p});
        }
    }


    if (!found) {
        cout << RED <<" |  Invalid username or password!  | \n"<< RESET;
        return;
    }

    
    ofstream out("users.txt", ios::trunc);

    for (auto& user : users) {
        out << user.first << " " << user.second << endl;
    }
    
    cout << GREEN << "|| Password changed successfully.. ||\n" << RESET ;
    }

bool User::adminRegister() {
    string a_name, passw, key;

    cout << BLUE << "Enter admin identification key: " << RESET ;
    key = getHiddenPassword();
    if (key != "2026") {
        cout << "Invalid key! You are not allowed to register as admin.\n";
        return false;
    }

    cout << BLUE <<"Enter admin username : "<< RESET;
    cin >> a_name;

    if(adminExists(a_name))
        {
        cout << RED <<"| Admin Username already exists.. |\n"<< RESET ;
        return true ;
        }

    cout << BLUE <<"Enter password : "<< RESET;
    passw = getHiddenPassword();

    ofstream file("admins.txt", ios::app);
    file << a_name << " " << hashPassword(passw) << endl;

    cout << GREEN << "| Admin registered successfully.. |\n"<< RESET;
    return true;
}

bool User::adminLogin(string& adminName) {
    string a_name, passw;

    cout << BLUE << " Enter admin username : "<< RESET;
    cin >> a_name;

    cout << BLUE <<" Enter admin password : "<< RESET;
    passw = getHiddenPassword();

    ifstream file("admins.txt");
    string u, p;

    while (file >> u >> p) {
        if (u == a_name && p == hashPassword(passw)) {
            adminName = a_name;
            cout << GREEN<< "| Admin login successful.. |\n"<< RESET;
            return true;
        }
    }

    cout << RED << "| Invalid admin credentials! |\n"<< RESET;
    return false;
}