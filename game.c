// 208306068 - Omri Naor

#include "mineSweeper.h"
#include "getch.h"
#include <stdio.h>

int main() {

    // Declare variables and set default values
    int col, row, level;
    bool win = FALSE;
    bool lose = FALSE;

    // Get input from the player to set the board
    printf("Enter row (max 20): ");
    scanf("%d", &row);
    printf("Enter col (max 20): ");
    scanf("%d", &col);
    printf("Enter level (1 - Easy, 2 - Medium, 3 - Hard): ");
    scanf("%d", &level);

    GameBoard gameBoard;
    bool pass = initBoard(&gameBoard, row, col, level);

    if(pass == FALSE)
    {
        printf("Failed to create board");
        return 0;
    }

    char input = getch(); // getch() here to avoid the 'enter a level' pressed enter to affect this variable (otherwise it gets an "enter" as the input here)
    int coordinates[] = {0, 0}; // Variable to hold the player's current location on the board
    printBoard(&gameBoard, coordinates);

    do
    {
        input = getch();

        if(input == FLAG_TILE)
            flagTile(&gameBoard, coordinates[0], coordinates[1]);

        if(input == UP && isLegal(&gameBoard, coordinates[0] - 1, coordinates[1]))
            coordinates[0] --;

        if(input == DOWN && isLegal(&gameBoard, coordinates[0] + 1, coordinates[1]))
            coordinates[0] ++;

        if(input == RIGHT && isLegal(&gameBoard, coordinates[0], coordinates[1] + 1))
            coordinates[1] ++;

        if(input == LEFT && isLegal(&gameBoard, coordinates[0], coordinates[1] - 1))
            coordinates[1] --;

        if(input == CLICK_TILE)
            clickTile(&gameBoard, coordinates[0], coordinates[1]);

        printBoard(&gameBoard, coordinates);

        // Check if won
        if(isWin(&gameBoard))
        {
            win = TRUE;
            break;
        }

        // Check if lost
        if(isLose(&gameBoard))
        {
            lose = TRUE;
            break;
        }

    }while(input != QUIT || win || lose);

    discoverMines(&gameBoard); // Discover all mines on the board
    printBoard(&gameBoard, coordinates);

    printf("\n\n");

    if(win)
        printf("Congratulations! You have won!");

    else if(lose)
        printf("Ouch! You hit a mine and lost!");
    else
        printf("Quitting the game to your request");

    freeBoard(&gameBoard);

    return 0;
}
