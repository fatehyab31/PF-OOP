#ifndef EASYCOMPUTER_H
#define EASYCOMPUTER_H

#include "ComputerPlayer.h"
using namespace std;

// Level 1: EasyComputer
// This computer ALWAYS picks Rock — completely predictable
// Inherits from ComputerPlayer which inherits from Player
class EasyComputer : public ComputerPlayer {
public:
    // Constructor
    EasyComputer() : ComputerPlayer("Easy Computer") {}

    // Overrides makeChoice() — always returns "Rock"
    string makeChoice() override {
        return "Rock";
    }
};

#endif