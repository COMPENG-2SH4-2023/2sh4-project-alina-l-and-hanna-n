// Guard against multiple inclusions of this header file
#ifndef PLAYER_H
#define PLAYER_H

// Include dependencies for the Player class
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

// Definition of the Player class
class Player
{
    // The exact implementation is to be filled in based on the project manual.

    // Only a subset of members are provided here.
    // More data members and functions will be needed to complete the design.

    public:
        // Enumeration for possible directions of the player's movement
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // Represents the direction state

        // Constructor and destructor for the Player class
        Player(GameMechs* thisGMRef);
        ~Player();

        // Method declarations:
        objPosArrayList* getPlayerPos(); // Method to get the player's position; Upgrade this in iteration 3.
        void updatePlayerDir();          // Method to update the player's direction.
        void movePlayer();               // Method to move the player.
        char getPlayerDir();             // Method to get the current direction of the player.
        bool checkFoodConsumption();     // Method to check if the player has consumed food.
        void increasePlayerLength();     // Method to increase the player's length.
        bool checkSelfCollision();       // Method to check for collision with itself.

    private:
        objPosArrayList *playerPos;  // A list to track the player's positions; Upgrade this in iteration 3.      
        enum Dir myDir;              // Variable to store the current direction of the player.

        // Reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

// End of the guard against multiple inclusions
#endif
