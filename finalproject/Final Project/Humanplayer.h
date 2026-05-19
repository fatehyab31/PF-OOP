#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include <iostream>
#include <cctype>  //provides toupper()
using namespace std;

// HumanPlayer inherits from Player
// Responsible for getting move input from the user
class HumanPlayer : public Player {
private:
    string lastChoice;   // Stores the human's last move (used by HardComputer)

public:
    // Constructor calls parent constructor with the name
    HumanPlayer(string playerName) : Player(playerName) {
        lastChoice = "";
    }

    // Overrides the pure virtual function from Player
    // Asks the user to type R, P, or S
    string makeChoice() override {
        string input;
        char ch;

        while (true) {
            cout << "\n  Enter your move (R = Rock, P = Paper, S = Scissors): ";
            cin >> input;

            // Convert to uppercase for easy comparison
            ch = toupper(input[0]);

            if (ch == 'R') {
                lastChoice = "Rock";
                return "Rock";
            }
            else if (ch == 'P') {
                lastChoice = "Paper";
                return "Paper";
            }
            else if (ch == 'S') {
                lastChoice = "Scissors";
                return "Scissors";
            }
            else {
                // Handle invalid input — keep asking
                cout << "  [!] Invalid input! Please enter R, P, or S.\n";
            }
        }
    }

    // Getter for last choice — HardComputer needs this to plan its move
    string getLastChoice() {
        return lastChoice;
    }
};

#endif