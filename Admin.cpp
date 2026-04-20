#include "Admin.h" //includes header file where admin class is defined
#include <iostream> // to use cin & cout
#include <fstream> // to use file stream funcs
#include <string> // to use string funcs
#include<vector> //dynamic arryas
#include <sstream>

using namespace std;


struct Question { //new data type to store questions, 4 options, correct option
    string q;
    string opt[4];
    int correct;
};

vector<Question> loadQuestions() {  // to convert txt file lines to array objects
    ifstream file("questions.txt");
    vector<Question> questions;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> parts;
        string part;

        while (getline(ss, part, '|')) {
            parts.push_back(part);
        }

        if (parts.size() != 6) continue;

        Question q;
        q.q = parts[0];
        for (int i = 0; i < 4; i++)
            q.opt[i] = parts[i + 1];

        q.correct = stoi(parts[5]);

        questions.push_back(q);
    }

    return questions;
}


void saveQuestions(vector<Question>& questions) {   //to convert vector objects to txt file lines
    ofstream file("questions.txt", ios::trunc);

    for (auto& q : questions) {
        file << q.q << "|"
             << q.opt[0] << "|"
             << q.opt[1] << "|"
             << q.opt[2] << "|"
             << q.opt[3] << "|"
             << q.correct << endl;
    }
}


void Admin::deleteQuestion() { //to delete the questions
    auto questions = loadQuestions();

    for (int i = 0; i < questions.size(); i++) {
        cout << i + 1 << ". " << questions[i].q << endl;
    }

    int index;
    cout << "Enter question number to delete: ";
    cin >> index;

    if (index < 1 || index > questions.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    questions.erase(questions.begin() + index - 1);

    saveQuestions(questions);

    cout << "Question deleted successfully!\n";
}


void Admin::editQuestion() {  // to edit questions
    auto questions = loadQuestions();

    for (int i = 0; i < questions.size(); i++) {
        cout << i + 1 << ". " << questions[i].q << endl;
    }

    int index;
    cout << "Enter question number to edit: ";
    cin >> index;

    if (index < 1 || index > questions.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    Question& q = questions[index - 1];

   cin.ignore();

    cout << "Enter new question: ";
    getline(cin, questions[index - 1].q);

    for (int i = 0; i < 4; i++) {
        cout << "Enter option " << i + 1 << ": ";
        getline(cin, questions[index - 1].opt[i]);
    }

    cout << "Enter correct option (1-4): ";
    cin >> questions[index - 1].correct;

    saveQuestions(questions);

    cout << "Question updated successfully!\n";
}


void Admin::re_quiz() {   // reset scores txt file
    ofstream file("scores.txt", ios::trunc);

    if (file) {
        cout << " ||  All quiz records cleared successfully.. ||\n";
    } else {
        cout << "Error clearing records.\n";
    }
}

void Admin::addQuestion() {  // to add question
    string question, opt1, opt2, opt3, opt4;
    int correct;

    cin.ignore(); // clear input buffer

    cout << "Enter question: ";
    getline(cin, question);

    cout << "Enter option 1: ";
    getline(cin, opt1);

    cout << "Enter option 2: ";
    getline(cin, opt2);

    cout << "Enter option 3: ";
    getline(cin, opt3);

    cout << "Enter option 4: ";
    getline(cin, opt4);

    cout << "Enter correct option number (1-4): ";
    cin >> correct;

    ofstream file("questions.txt", ios::app);
    file << question << "|"
         << opt1 << "|"
         << opt2 << "|"
         << opt3 << "|"
         << opt4 << "|"
         << correct << endl;

    cout << "Question added successfully!\n";
}


void Admin::viewQuestions() { // to view questions
    ifstream file("questions.txt");
    string line;
    int qNo = 1;

    cout << "\n=== ALL QUESTIONS ===\n";
    while (getline(file, line)) {
        cout << qNo++ << ". " << line << endl;
    }
}
