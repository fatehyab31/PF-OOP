#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "HumanPlayer.h"
#include "HardComputer.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// ─── Windows Console Color Helpers ───────────────────────────────────────────
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void setColorBG(int fg, int bg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg * 16 + fg);
}
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// Game class — manages one complete Best-of-3 match
class Game {
private:
    HumanPlayer* human;
    Player* computer;
    HardComputer* hardComp;
    int totalRounds;

   
    int powerUpsLeft;    
    bool powerUpActive;  

    // Determine round winner — returns "human", "computer", or "tie"
    string determineWinner(string h, string c) {
        if (h == c) return "tie";
        if ((h == "Rock" && c == "Scissors") ||
            (h == "Paper" && c == "Rock") ||
            (h == "Scissors" && c == "Paper"))
            return "human";
        return "computer";
    }

   
    void showPowerUpStatus() {
        cout << "\n  ";
        if (powerUpsLeft > 0) {
            setColorBG(0, 14); 
            cout << "  ** POWER UP available! (" << powerUpsLeft << " left) **  ";
            resetColor();
            setColor(14);
            cout << "\n  Use your Power Up this round? (Y/N): ";
            resetColor();

            char choice;
            cin >> choice;

            if (toupper(choice) == 'Y') {
              
                powerUpActive = true;
                powerUpsLeft--;   

                setColorBG(0, 14); 
                cout << "\n  ** POWER UP ACTIVATED! Win = 2 points! **  ";
                resetColor();
                cout << "\n";
            }
            else {
                powerUpActive = false;
                setColor(13);
                cout << "\n  Power Up saved for later!\n";
                resetColor();
            }
        }
        else {
            
            setColor(12); 
            cout << "  No Power Ups remaining.\n";
            resetColor();
            powerUpActive = false;
        }
    }

    void printRoundBox(int roundNum, string humanMove, string compMove,
        string result, int hScore, int cScore) {

        setColor(13); 
        cout << "\n  +-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+\n";

        
        cout << "  |  ";
        setColorBG(15, 5); 
        cout << " Round " << roundNum << " of " << totalRounds << " ";
        resetColor(); setColor(15);
        cout << "                                       ";
        setColor(13);
        cout << "|\n";

        
        if (powerUpActive) {
            cout << "  |  ";
            setColorBG(0, 14); 
            cout << "  ** POWER UP ACTIVEED THIS ROUND! **  ";
            resetColor(); setColor(15);
            cout << "              ";
            setColor(13); cout << "|\n";
        }
       

        cout << "  +-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+\n";

        cout << "  |   ";
        setColor(14); 
        cout << human->getName() << " played: ";
        setColorBG(0, 13); 
        cout << " " << humanMove << " ";
        resetColor(); setColor(15);
       

        cout << "  +-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+\n";

        cout << "  |   ";
        if (result == "human") {
            if (powerUpActive) {
             
                setColorBG(0, 10); 
                cout << "  ** POWER UP WIN! +2 Points! **     ";
            }
            else {
                setColorBG(0, 10);
                cout << "  ** Yay! YOU WIN THIS ROUND! **     ";
            }
            resetColor(); setColor(15);
            cout << "            ";
            setColor(13); cout << "|\n";
        }
        else if (result == "computer") {
            setColorBG(15, 4); 
            if (powerUpActive) {
                cout << "  ** Power Up WASTED! You lost! **  ";
            }
            else {
                cout << "  ** Aw! Computer wins this round! **";
            }
            resetColor(); setColor(15);
            cout << "            ";
            setColor(13); cout << "|\n";
        }
        else {
            setColorBG(0, 14); 
            if (powerUpActive) {
                cout << "  ** Tie! Power Up wasted too! **   ";
            }
            else {
                cout << "  ** It's a Tie! How cute! **       ";
            }
            resetColor(); setColor(15);
            cout << "            ";
            setColor(13); cout << "|\n";
        }

        cout << "  |   ";
        setColor(15); cout << "Score:  ";
        setColorBG(0, 10); cout << " You: " << hScore << " ";
        resetColor(); setColor(15); cout << "  vs  ";
        setColorBG(15, 4); cout << " Computer: " << cScore << " ";
        resetColor(); setColor(15);
        cout << "         ";
        setColor(14);
        cout << "PU:" << powerUpsLeft << " ";//show power ups
        setColor(13); cout << "|\n";

        cout << "  +-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+\n";
        resetColor();
    }

public:
    Game(HumanPlayer* h, Player* comp, int level) {
        human = h;
        computer = comp;
        totalRounds = 3;
        powerUpsLeft = 1;     // player gets 1 power 
        powerUpActive = false;
        hardComp = (level == 3) ? dynamic_cast<HardComputer*>(comp) : nullptr;
    }

  
    void playMatch() {
        human->resetScore();
        computer->resetScore();
        powerUpsLeft = 1;     
        powerUpActive = false;

        setColor(13);
        cout << "\n  -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
        setColor(15); cout << "  Playing against: ";
        setColorBG(15, 4);
        cout << " " << computer->getName() << " ";
        resetColor(); cout << "\n";

   
        setColorBG(0, 14); 
        cout << "  ** You have 1 POWER UP this match!          **\n";
        cout << "  ** Use it to get DOUBLE points if you win!  **\n";
        resetColor();

        setColor(13);
        cout << "  -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
        resetColor();

       
        for (int round = 1; round <= totalRounds; round++) {
            setColor(13);
            cout << "\n  ~ ~ ~ Round " << round << " ~ ~ ~";
            resetColor();

            
            showPowerUpStatus();

          
            string humanMove = human->makeChoice();
            string compMove = computer->makeChoice();

          
            string result = determineWinner(humanMove, compMove);

            if (result == "human") {
                if (powerUpActive) {
                 
                    human->incrementScore();
                    human->incrementScore();
                }
                else {
                    human->incrementScore();
                }
            }
            if (result == "computer") computer->incrementScore();

            powerUpActive = false;

           
            printRoundBox(round, humanMove, compMove, result,
                human->getScore(), computer->getScore());

            
            if (hardComp != nullptr)
                hardComp->setPlayerLastMove(humanMove);
        }

        cout << "\n";
        setColor(13);
        cout << "  -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
        cout << "  ";

        if (human->getScore() > computer->getScore()) {
            setColorBG(0, 10); 
            cout << "  ***YOU WIN THE MATCH "
                << human->getScore() << "-" << computer->getScore() << "! ***  ";
        }
        else if (computer->getScore() > human->getScore()) {
            setColorBG(15, 4); 
            cout << "  *** Computer wins "
                << computer->getScore() << "-" << human->getScore()
                << "... Don't give up! ***  ";
        }
        else {
            setColorBG(0, 14);
            cout << "  *** It's a Draw "
                << human->getScore() << "-" << computer->getScore()
                << "! So close! ***  ";
        }

        resetColor(); cout << "\n";
        setColor(13);
        cout << "  -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
        resetColor();
    }
};

#endif