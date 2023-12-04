#ifndef GAMEMECHS_H
#define GAMEMECHS_H

// Including necessary libraries and header files
#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

// Definition of the GameMechs class
class GameMechs
{
    // Private members are only accessible within the class
    private:
        char input; // Variable to store the latest input character
        bool loseFlag; // Flag to indicate whether the player has lost
        bool exitFlag; // Flag to indicate whether the game should exit

        int boardSizeX; // Width of the game board
        int boardSizeY; // Height of the game board

        long int score; // Variable to store the player's score
        objPos fPos; // Position of the food item on the board

    // Public members are accessible from outside the class
    public:
        GameMechs(); // Default constructor
        GameMechs(int boardX, int boardY); // Constructor with board size parameters
        ~GameMechs(); // Destructor

        // Getter and setter methods for various class properties
        bool getExitFlagStatus();
        void setExitTrue();

        bool getLoseFlagStatus();
        void setLoseFlagTrue();

        long int getScore();
        void incrementScore();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        void generateFood(objPosArrayList* blockOff); // Method to generate food on the board
        void getFoodPos(objPos &returnPos); // Method to get the current position of the food
};

#endif
