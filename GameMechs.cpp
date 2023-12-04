#include "GameMechs.h"    // Include the GameMechs header file
#include "MacUILib.h"     // Include a custom Mac UI Library for handling input
#include <iostream>       // Include the standard I/O library
#include "objPos.h"       // Include the objPos header file for object positioning
#include <cstdlib>        // Include the standard library for general utilities
#include <time.h>         // Include the time library for seeding the random number generator

// Default constructor
GameMechs::GameMechs()
{
    // Initialize basic game variables
    input = 0;
    score = 0; // Initialize score
    exitFlag = false; // Flags for game exit and lose conditions
    loseFlag = false;
    boardSizeX = 30; // Set default board size
    boardSizeY = 15;

    // Initialize food position to an out-of-bounds position
    fPos.setObjPos(-10, -10, 'o');
}

// Parameterized constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    // Initialize game variables with provided board dimensions
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;

    // Seed the random number generator
    srand(time(NULL));

    // Generate random position for food, ensuring it's not on the border
    int x, y;
    do
    {
        x = 1 + rand() % (boardSizeX - 2);
        y = 1 + rand() % (boardSizeY - 2);
    } while (x == fPos.x && y == fPos.y);
    
    fPos.setObjPos(x, y, 'o'); // Set the food's position
}

// Destructor
GameMechs::~GameMechs()  
{
    // Currently empty. If dynamic memory allocation is used, it needs to be freed here.
}

// Getters and setters for various game flags and properties
bool GameMechs::getExitFlagStatus() { 
    return exitFlag; 
    }

bool GameMechs::getLoseFlagStatus() { 
    return loseFlag; 
    }

void GameMechs::setLoseFlagTrue() { 
    loseFlag = true; 
    }

long int GameMechs::getScore() { 
    return score; 
    }

void GameMechs::incrementScore() { 
    score += 1; 
    } // Increment score

char GameMechs::getInput()
{
    if (MacUILib_hasChar()) {
        input = MacUILib_getChar();
    } 
    return input;
}

int GameMechs::getBoardSizeX() { 
    return boardSizeX; 
    } //get board width

int GameMechs::getBoardSizeY() { 
    return boardSizeY; 
    }//get board height

void GameMechs::setExitTrue() { 
    exitFlag = true; 
    }

void GameMechs::setInput(char this_input) { 
    input = this_input; 
    }

void GameMechs::clearInput() { 
    input = 0; 
    }

// Method to generate food in a random position on the board, avoiding snake's body
void GameMechs::generateFood(objPosArrayList* blockOff) {
    int x, y;
    do {
        // Generate a new position for the food
        x = 1 + rand() % (boardSizeX - 2);
        y = 1 + rand() % (boardSizeY - 2);

        // Check for overlap with snake's body
        bool overlap = false;
        for (int i = 0; i < blockOff->getSize(); i++) {
            objPos tempPos;
            blockOff->getElement(tempPos, i);
            if (tempPos.x == x && tempPos.y == y) {
                overlap = true;
                break;
            }
        }
        if (!overlap) break; // Break loop if no overlap
    } while (true);

    // Set the new food position
    fPos.setObjPos(x, y, 'o');
}

// Method to get the current food position
void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(fPos);
}
