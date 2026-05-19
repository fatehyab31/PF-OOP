#ifndef MEDIUMCOMPUTER_H
#define MEDIUMCOMPUTER_H

#include "ComputerPlayer.h"
using namespace std;

// Level 2: MediumComputer
// This computer picks completely randomly each round
// Inherits from ComputerPlayer
class MediumComputer : public ComputerPlayer {
public:
    // Constructor
    MediumComputer() : ComputerPlayer("Medium Computer") {}

    // Overrides makeChoice() — picks Rock, Paper, or Scissors randomly
    string makeChoice() override {
        return randomMove();   // uses the helper from ComputerPlayer
    }
};

#endif