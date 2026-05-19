#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

// Abstract base class for all players (Human and Computer)
// Contains common properties: name and score
class Player {
protected:
    string name;   // Player's name
    int score;     // Player's current score

public:
    // Constructor to initialize name and score
    Player(string playerName) {
        name = playerName;
        score = 0;
    }

    // Pure virtual function - every subclass MUST implement their own version
    // This is what makes Player an abstract class
    virtual string makeChoice() = 0;

    // Getter for name
    string getName() {
        return name;
    }

    // Getter for score
    int getScore() {
        return score;
    }

    // Increases score by 1 when player wins a round
    void incrementScore() {
        score++;
    }

    // Resets score back to 0 for a new match
    void resetScore() {
        score = 0;
    }

    // Virtual destructor (good practice for abstract classes)
    virtual ~Player() {}
};

#endif