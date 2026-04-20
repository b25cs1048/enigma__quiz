#include <iostream>
#include <limits>
#include "User.h"
#include "Quiz.h"
#include "Leaderboard.h"
#include "Admin.h"
using namespace std;

int main() {
    User user;    // objects names
    Quiz quiz;
    Leaderboard lb;
    Admin admin;

    int choice;
    string loggedInUser;   // strings ke names
    string adminName;

    while (true) {
        cout << "\n=== QUIZ SYSTEM ===\n";   // options for user/admin
        cout << "1. Register\n";
        cout << "2. Login & Take Quiz\n";
        cout << "3. Admin Login\n";
        cout << "4. Change Password\n";
        cout << "5. Register Admin\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        if(!(cin>>choice)){
            cin.clear();
            cout<< "Invalid input! Please enter a number.\n";
        continue;
        }

        switch (choice) {

        case 1:
            user.registerUser();
            break;

        case 2:
            if (user.loginUser(loggedInUser)) {
                quiz.startQuiz(loggedInUser);
            }
            break;

        case 3:
            if (user.adminLogin(adminName)) {
                int adminChoice;
                while (true) {
                    cout << "\n=== ADMIN PANEL ===\n";   // options for admin
                    cout << "1. View Leaderboard\n";
                    cout << "2. Add Question\n";
                    cout << "3. View Questions\n";
                    cout << "4. Reset Scores\n";
                    cout << "5. Delete Question\n";
                    cout << "6. Edit Question\n";
                    cout << "7. Logout\n";
                    cout << "Enter choice: ";
                    cin >> adminChoice;
                    

                    if (adminChoice == 7) {
                           break;
                    }
                    else if (adminChoice == 1) {
                        lb.showLeaderboard();
                    }
                    else if (adminChoice == 2) {
                        admin.addQuestion();
                    }
                    else if (adminChoice == 3) {
                        admin.viewQuestions();
                    }
                    else if (adminChoice == 4) {
                        admin.re_quiz();
                    }
                    else if (adminChoice == 5) {
                          admin.deleteQuestion();
                    }
                    else if (adminChoice == 6) {
                          admin.editQuestion();
                    }
                    else {
                        cout << "Invalid choice!\n";
                    }
                }
            }
            break;
        case 4:
            user.change_passw_user();
            break;
        
        case 5:
            user.adminRegister();
            break;
        case 6:
            cout << "Exiting program...\n";    //program ends
            return 0;

        default:
            cout << "Invalid choice.\n";    
        }
    }
}
