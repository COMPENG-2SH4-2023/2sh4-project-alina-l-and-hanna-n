#include "Player.h"
#include "objPosArrayList.h"
#include "objPos.h"
GameMechs gameMech;

// Constructor for the Player class
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;  // Stores a reference to the Game Mechanics
    myDir = STOP;  // Initial direction of the player is set to STOP

    // Initialize player position at the center of the game board
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    
    playerPos = new objPosArrayList();  // Create a new list to track player positions
    playerPos->insertHead(tempPos);     // Insert the initial position to the list
}

// Destructor for the Player class
Player::~Player()
{
    delete playerPos;  // Clean up the dynamically allocated playerPos
}

// Getter method for player's position
objPosArrayList* Player::getPlayerPos()
{
    return playerPos;  // Returns the list of player positions
}

// Method to update the player's direction based on input
void Player::updatePlayerDir()
{
    char lastInput = 0; // Static variable to remember the last input (currently unused)
    char inputUpdate = mainGameMechsRef->getInput(); // Get the latest input

    switch(inputUpdate)
    {
        case ' ': // If spacebar is pressed, exit the game
            mainGameMechsRef -> setExitTrue();
            break;        

        case 'w': // Move up unless currently moving down
            if(myDir != DOWN) myDir = UP;
            break;
        
        case 'a': // Move left unless currently moving right
            if(myDir != RIGHT) myDir = LEFT;
            break;
          
        case 's': // Move down unless currently moving up
            if(myDir != UP) myDir = DOWN;
            break;

        case 'd': // Move right unless currently moving left
            if(myDir != LEFT) myDir = RIGHT;
            break;

        default:
            break; // Do nothing for other inputs
    }
}

// Method to move the player based on the current direction
void Player::movePlayer()
{
    int BOARD_HEIGHT = mainGameMechsRef -> getBoardSizeY();
    int BOARD_WIDTH = mainGameMechsRef -> getBoardSizeX();
    objPos playerPosXY;

    playerPos->getHeadElement(playerPosXY); // Get the current player position

    // Update player position based on the current direction
    switch (myDir)
    {
        case UP:
            playerPosXY.y -= 1;
            if (playerPosXY.y < 1) playerPosXY.y = BOARD_HEIGHT - 2;
            break;
        case DOWN:
            playerPosXY.y++;
            if (playerPosXY.y >= BOARD_HEIGHT-1) playerPosXY.y = 1;
            break;
        case LEFT:
            playerPosXY.x--;
            if (playerPosXY.x < 1) playerPosXY.x = BOARD_WIDTH - 2;
            break;
        case RIGHT:
            playerPosXY.x++;
            if (playerPosXY.x >= BOARD_WIDTH-1) playerPosXY.x = 1;
            break;
        default:
            break; // Do nothing if the direction is STOP or undefined
    }
    
    playerPos->insertHead(playerPosXY); // Update the position list with the new position
    playerPos->removeTail();            // Remove the oldest position from the list
}

// Method to get the player's current direction
char Player::getPlayerDir()
{
    // Return a character representing the current direction of the player
    switch(myDir)
    {
        case UP:
            return 'U';
        case DOWN:
            return 'D';
        case LEFT:
            return 'L';
        case RIGHT:
            return 'R';
        default:
            return '\0'; // Return null character if no direction is set
    }
}

// Method to check if the player has consumed food
bool Player::checkFoodConsumption() 
{
    playerPos = getPlayerPos();  // Get the current position of the player
    objPos headPos;
    playerPos->getHeadElement(headPos);  // Get the head position of the player

    objPos fPos;
    mainGameMechsRef->getFoodPos(fPos);  // Get the current position of the food

    // Return true if the head position is the same as the food position
    return headPos.isPosEqual(&fPos);
}

// Method to increase the length of the player
void Player::increasePlayerLength() 
{
    playerPos = getPlayerPos();  // Get the current position of the player

    objPos newHeadPos;
    playerPos->getHeadElement(newHeadPos);  // Create a new head position based on the current one

    playerPos->insertHead(newHeadPos);  // Add the new position to the player's body
}

// Method to check if the player has collided with itself
bool Player::checkSelfCollision() 
{
    playerPos = getPlayerPos();  // Get the current position of the player
    objPos headPos;
    playerPos->getHeadElement(headPos);  // Get the head position of the player

    // Iterate through the player's body to check for self-collision
    for (int i = 1; i < playerPos->getSize(); i++) {
        objPos bodyPart;
        playerPos->getElement(bodyPart, i);
        
        if (i > 0 && headPos.isPosEqual(&bodyPart)) {
            // If the head collides with any other body part, return true
            return true;
        }
    }
    
    // Return false if no collision is detected
    return false;
}
