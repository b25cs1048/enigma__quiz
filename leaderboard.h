// #ifndef LEADERBOARD_H
// #define LEADERBOARD_H

// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string>
// using namespace std;

// class Leaderboard
// {
// public:
//     bool hasAttempted(string username);
//     int getUserScore(string username);
//     void totalPlayers();
//     void saveScore(string username, int score, int total);
//     void showLeaderboard();
//      void showLeaderboard(int totalQuestions);
// };

// #endif
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
using namespace std;

class Leaderboard
{
public:
    bool hasAttempted(string username);
    void totalPlayers();

    // Save score with total questions
    void saveScore(string username, int score, int total);

    void showLeaderboard();
};

#endif