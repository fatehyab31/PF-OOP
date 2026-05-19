#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include <cstdlib>   // for rand()
#include <ctime>     // for time() to seed random
using namespace std;

// Abstract base class for all computer difficulty levels
// Inherits from Player and acts as a blueprint for Easy, Medium, Hard computers
class ComputerPlayer : public Player {
public:
    // Constructor — passes name up to Player constructor
    ComputerPlayer(string playerName) : Player(playerName) {}

    // Still pure virtual — each difficulty must define its own makeChoice()
    virtual string makeChoice() = 0;

    // Used by Medium and Hard (for first move) computers
    string randomMove() {
        int r = rand() % 3;   // generates 0, 1, or 2
        if (r == 0) return "Rock";
        if (r == 1) return "Paper";
        return "Scissors";
    }

    // Virtual destructor
    virtual ~ComputerPlayer() {}
};

#endif
