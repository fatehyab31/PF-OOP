// ================================================================
//   ROCK PAPER SCISSORS - 3 LEVEL CHALLENGE
//   Main.cpp — Entry point, menu, game loop
// ================================================================

#include <iostream>
#include <string>
#include <cstdlib>  //Contains rand() and srand()
#include <ctime>    //Used for random seed with current time
#include <windows.h>   //set the console window title

#include "HumanPlayer.h"
#include "EasyComputer.h"
#include "MediumComputer.h"
#include "HardComputer.h"
#include "Game.h"
#include "Player.h" 

using namespace std;

void showBanner() {
    cout << "\n";
    setColorBG(13, 5); 
    cout << "                                                       ";
    resetColor(); cout << "\n";

    setColorBG(15, 5);
    cout << "      ~ * ~ ROCK  PAPER  SCISSORS ~ * ~               ";
    resetColor(); cout << "\n";

    setColorBG(14, 5);
    cout << "           3  L E V E L   C H A L L E N G E           ";
    resetColor(); cout << "\n";

    setColorBG(13, 5);
    cout << "                                                       ";
    resetColor(); cout << "\n\n";
}

void showDivider() {
    setColor(13); 
    cout << "  -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    resetColor();
}


void showMenu() {
    cout << "\n";
    setColor(13); 
    cout << "  +-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+\n";
    cout << "  |  ";
    setColorBG(15, 5); 
    cout << "   ~ Choose Your Difficulty Level! ~   ";
    resetColor(); setColor(13);
    cout << "  |\n";
    cout << "  +-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+\n";

    cout << "  |                                                     |\n";

    cout << "  |   ";
    setColorBG(0, 10); // Black on Green
    cout << " 1. Easy ";
    resetColor(); setColor(15);
    // Computer always picks Rock   
    setColor(13); cout << "|\n";

    cout << "  |                                                     |\n";

    cout << "  |   ";
    setColorBG(0, 14); // Black on Yellow
    cout << " 2. Medium ";
    resetColor(); setColor(15);
    // Computer picks randomly
    setColor(13); cout << "|\n";

    cout << "  |                                                     |\n";

    cout << "  |   ";
    setColorBG(15, 4); // White on Red
    cout << " 3. Hard ";
    resetColor(); setColor(15);
    // Computer counters your last move
    setColor(13); cout << "|\n";

    cout << "  |                                                     |\n";

    cout << "  |   ";
    setColorBG(15, 5); // White on Magenta
    cout << " 4. Quit ";
    resetColor(); setColor(15);
    cout << "  -- Exit the game                       ";
    setColor(13); cout << "|\n";

    cout << "  |                                                     |\n";
    cout << "  +-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+\n";
    resetColor();

    setColor(13);
    cout << "\n  >> Your choice: ";
    resetColor();
}

// ─── MAIN ─────────────────────────────────────────────────────────────────────
int main() {
    // Set window title
    SetConsoleTitleA("~ Rock Paper Scissors ~ Girly Edition ~");

    // Set the ENTIRE console background to magenta/pink
    system("color 5F");

    // Seed random
    srand((unsigned int)time(0));

    // Welcome screen
    showBanner();
    showDivider();
    setColor(13);
    cout << "\n   What's your name? : ";
    resetColor();
    string playerName;
    cin >> playerName;

    setColor(13);
    cout << "\n  Welcome, " << playerName << "! Let's play! <3\n";
    resetColor();

    HumanPlayer human(playerName);
    char playAgain = 'Y';

    // ─── Main game loop ───────────────────────────────────────────────────
    while (toupper(playAgain) == 'Y') {

        showBanner();
        showMenu();

        int levelChoice;
        cin >> levelChoice;

        

        while (cin.fail() || levelChoice < 1 || levelChoice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(12);
            cout << "  [!] Oops! Please enter 1, 2, 3, or 4: ";
            resetColor();
            cin >> levelChoice;
        }
      
        if (levelChoice == 4) {
            setColorBG(15, 5);
            cout << "\n  Byeee " << playerName << "! Come back soon! <3  ";
            resetColor();
            cout << "\n\n";
            break;
        }

        // Polymorphism — base pointer holds any computer type
        Player* computer = nullptr;
        if (levelChoice == 1) computer = new EasyComputer();
        else if (levelChoice == 2) computer = new MediumComputer();
        else if (levelChoice == 3) computer = new HardComputer();

        Game game(&human, computer, levelChoice);
        game.playMatch();
        showDivider();
        setColor(13);
        cout << "\n  Wanna go again, " << playerName << "? (Y/N): ";
        resetColor();
        cin >> playAgain;

        delete computer;
        computer = nullptr;
    }

    if (toupper(playAgain) != 'Y') {
        cout << "\n";
        showDivider();
        setColorBG(15, 5);
        cout << "   Thanks for playing, " << playerName << "! You're a star! <3  ";
        resetColor();
        cout << "\n";
        showDivider();
        cout << "\n";
    }

    return 0;
}
