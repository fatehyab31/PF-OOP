#ifndef HARDCOMPUTER_H
#define HARDCOMPUTER_H

#include "ComputerPlayer.h"
using namespace std;

// Level 3: HardComputer
// This computer REMEMBERS your last move and picks the move that BEATS it
// First move of the game is random since there is no previous move yet so that is why srand and rand are uesd.
class HardComputer : public ComputerPlayer {
private:
    string playerLastMove;   // Stores what the human player chose last round

public:
    // Constructor — starts with no knowledge of player's last move
    HardComputer() : ComputerPlayer("Hard Computer") {
        playerLastMove = "";   // empty means no last move yet (first round)
    }

    // Called by Game class after each round to update what the human played
    void setPlayerLastMove(string move) {
        playerLastMove = move;
    }

    // Overrides makeChoice()
    // If no last move exists (first round), pick randomly
    // Otherwise, pick the move that BEATS the player's last move
    string makeChoice() override {
        if (playerLastMove == "") {
            // First round: no info yet, go random
            return randomMove();
        }

        // Counter-strategy logic:
        // Player played Rock  → Computer plays Paper  (Paper beats Rock)
        // Player played Paper → Computer plays Scissors (Scissors beats Paper)
        // Player played Scissors → Computer plays Rock (Rock beats Scissors)
        if (playerLastMove == "Rock")     return "Paper";
        if (playerLastMove == "Paper")    return "Scissors";
        if (playerLastMove == "Scissors") return "Rock";

        // Fallback (should never reach here)
        return randomMove();
    }
};

#endif
