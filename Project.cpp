// Include necessary header files
#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

// Use the standard namespace to avoid typing 'std::' before standard library functions
using namespace std;

// Define a constant for delay
#define DELAY_CONST 100000

// Declare global variables for game mechanics and player
GameMechs* gameMechs;
Player* player;
int inputMain = 0; // Currently unused variable for input

// Function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Main function
int main(void)
{
    Initialize(); // Initialize game components

    // Main game loop
    while(gameMechs->getExitFlagStatus() == false)  
    {
        GetInput();     // Get player input
        RunLogic();     // Update game logic
        DrawScreen();   // Render the game screen
        LoopDelay();    // Delay for a fixed amount of time
    }

    CleanUp(); // Clean up resources upon exiting the loop
}

// Function to initialize game components
void Initialize(void)
{
    MacUILib_init(); // Initialize the UI library
    MacUILib_clearScreen(); // Clear the screen

    // Create game mechanics and player objects
    gameMechs = new GameMechs(30, 15); // Initialize GameMechs with board size
    player = new Player(gameMechs); // Initialize Player with a reference to GameMechs
}

// Function to process player input
void GetInput(void)
{
    gameMechs->getInput(); // Get input from the player
}

// Function to update game logic
void RunLogic(void)
{
    player->updatePlayerDir(); // Update the player's direction
    player->movePlayer(); // Move the player based on the updated direction

    // Check for self-collision
    if (!player->checkSelfCollision()) {
        objPosArrayList* playerPosList = player->getPlayerPos();

        // Check if the player has consumed food
        if (player->checkFoodConsumption()) {
            player->increasePlayerLength(); // Increase player length
            gameMechs->incrementScore(); // Increment score
            gameMechs->generateFood(playerPosList); // Generate new food on the game board
        }

        gameMechs->clearInput(); // Clear the input after processing
    } else {
        gameMechs->setLoseFlagTrue(); // Set lose flag on collision
        gameMechs->setExitTrue(); // Set exit flag to break the game loop
    }
}

// Function to draw the game screen
void DrawScreen(void)
{
    MacUILib_clearScreen(); // Clears the screen before drawing the new frame
    int x, y;

    // Get the player's current positions
    objPosArrayList* playerPosList = player->getPlayerPos();
    objPos tempBody;

    // Get the current food position
    objPos fPos;
    gameMechs->getFoodPos(fPos);

    bool drawn;

    // Get the board dimensions
    int BOARD_HEIGHT = gameMechs->getBoardSizeY();
    int BOARD_WIDTH = gameMechs->getBoardSizeX();

    // Iterate through each cell of the board
    for (y = 0; y < BOARD_HEIGHT; y++) {
        for (x = 0; x < BOARD_WIDTH; x++) {
            drawn = false;

            // Check if any part of the player is in the current cell
            for(int k = 0; k < playerPosList->getSize(); k++)
            {
                playerPosList->getElement(tempBody, k);
                if(tempBody.x == x && tempBody.y == y)
                {
                    MacUILib_printf("%c", tempBody.symbol); // Draw the player part
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;

            // Draw the board borders
            if (y == 0 || y == (BOARD_HEIGHT - 1) || x == 0 || x == (BOARD_WIDTH - 1)) {
                MacUILib_printf("#");
            } 
            // Draw the food
            else if (y == fPos.y && x == fPos.x) {
                MacUILib_printf("%c", fPos.symbol); 
            } 
            // Draw empty space
            else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n"); // New line at the end of each row
    }

    // Display debug messages and game information
    MacUILib_printf("Score: %d\n", gameMechs->getScore()); 
    MacUILib_printf("======== DEBUG MESSAGE ========\n");
    MacUILib_printf("Board Size: %d X %d\n", gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY());
    MacUILib_printf("Player Direction: %c\n", player->getPlayerDir());
    MacUILib_printf("Player Position: \n");
    for(int l = 0; l < playerPosList->getSize(); l++)
    {
        playerPosList->getElement(tempBody, l);
        MacUILib_printf("<%d, %d> ", tempBody.x, tempBody.y);
    }
    MacUILib_printf("\nFood Position: <%d, %d>\n", fPos.x, fPos.y);
}

// Function to introduce a delay in the game loop
void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // Introduce a fixed delay
}

// Function to clean up resources and display end messages
void CleanUp(void)
{
    MacUILib_clearScreen(); // Clear the screen

    // Check game status and display the appropriate message
    if (gameMechs->getExitFlagStatus() == true && gameMechs->getLoseFlagStatus() == true)
    {
        MacUILib_printf("YOU LOST! Your Score: %d", gameMechs->getScore()); // Lost message
    }
    else
    {
        MacUILib_printf("GAME ENDED! Your Score: %d", gameMechs->getScore()); // Endgame message
    }

    // Finalize the UI library and release memory
    MacUILib_uninit();
    delete gameMechs;
    delete player;
}
