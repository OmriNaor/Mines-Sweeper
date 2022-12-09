// 208306068 - Omri Naor

#include "mineSweeper.h"
#include "colorPrint.h"
#include "getch.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 Function creates the board and sets default values
 @param g - pointer to the game board
 @param rows - number of rows in the game board
 @param cols - number of cols in the game board
 @param level - level defines the amount of mines (easy/medium/hard)

 @return - true is succeeded, else false.
*/
bool initBoard(GameBoard *g, int rows, int cols, int level)
{
    if(rows > MAX_BOARD_DIM)
        rows = MAX_BOARD_DIM;

    if(cols > MAX_BOARD_DIM)
        cols = MAX_BOARD_DIM;

    if(cols <= 0)
        cols = MIN_BOARD_DIM;

    if(rows <= 0)
        rows = MIN_BOARD_DIM;

    // Set board values + malloc the board
    g->rows = rows;
    g->cols = cols;
    g->isMineClicked = FALSE;
    g->board = (Tile **)malloc(rows * sizeof(Tile*));

    if(g->board == NULL)
        return FALSE;

    for(int i = 0 ; i < rows ; i++)
    {
        g->board[i] = (Tile *)malloc(cols * sizeof(Tile));

        if(g->board[i] == NULL)
            return FALSE;
    }


    // Reset default values for every tile in the board
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            g->board[i][j].isMine = FALSE;
            g->board[i][j].isVisible = FALSE;
            g->board[i][j].isFlagged = FALSE;
            g->board[i][j].numOfMines = 0;
        }

    // In case of illegal level input
    if(level > HARD)
        level = HARD;
    else if(level < EASY)
        level = EASY;

    populateMines(g, level);
    g->hiddenTiles = (cols * rows) - g->totalMines;
    markNumbers(g);

    return TRUE;
}

/*
Function populates the mines randomly on the board, depending on the given level
@param g - pointer to the game board
@param level - level defines the amount of mines (easy/medium/hard)
*/
void populateMines(GameBoard *g, int level)
{
    int amount; // Variable to hold the amount of mines
    int size = g->rows * g->cols; // Variable to hold the size of the whole board
    srand(time(NULL));

    // Choose amount of mines depending on the given level and its percentage
    if(level == EASY)
        amount = EASY_LEVEL_PERCENT * size / 100;
    if(level == MEDIUM)
        amount = MEDIUM_LEVEL_PERCENT * size / 100;
    if(level == HARD)
        amount = HARD_LEVEL_PERCENT * size / 100;

    int randomCol;
    int randomRow;

    g->totalMines = amount; // Update the board's total mines with the final amount
    int i = 0;
    // Set random location for mines
    do
    {
        randomCol = rand() % (g->cols);
        randomRow = rand() % (g->rows);

        if(!g->board[randomRow][randomCol].isMine)
        {
            g->board[randomRow][randomCol].isMine = TRUE;
            g->board[randomRow][randomCol].numOfMines = -1;

            i++;
        }

    }while(i < amount);
}

/*
Function checks each tile on the given board and marks it with a number (which defines the amount of mines around him)
@param g - pointer to the game board
*/
void markNumbers(GameBoard *g)
{
    // Directions to check all 8 neighbors
    int directionArr[8][2] = {
            {0, 1},
            {0, -1},
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {1, 1},
            {1, 0},
            {1, -1},
    };

    // Check every tile in the board, if a mine, add 1 to numOfMines of each neighbor
    int newI, newJ, index;

    for (int i = 0; i < g->rows; i++)
    {
        for (int j = 0; j < g->cols; j++)
        {
            index = 0; // Index in the directions arr

            if(g->board[i][j].isMine)
            {
                for(int k = 0 ; k < 8 ; k++)
                {
                    newI = directionArr[index][0];
                    newJ = directionArr[index][1];
                    index++;

                    newI += i;
                    newJ += j;
                    // If the neighbor is inside the board and isn't a mine
                    if (isLegal(g, newI, newJ) && !(g->board[newI][newJ].isMine))
                        g->board[newI][newJ].numOfMines++;
                }
            }
        }
    }
}

/*
Function checks and handles the tile located in the given location according to its current status
@param g - pointer to the game board
@param row - row of the required location
@param col - col of the required location
*/
void clickTile(GameBoard *g, int row, int col)
{

    // If illegal location
    if(!isLegal(g, row, col))
        return;

    // If the location is already visible
    if(g->board[row][col].isVisible)
        return;

    // If the location is flagged
    if(g->board[row][col].isFlagged)
        return;

    // If the required location's number is higher than 0
    if(g->board[row][col].numOfMines > 0)
    {
        g->board[row][col].isVisible = TRUE;
        g->hiddenTiles--; // Tile is not a mine
        return;
    }

    // If the required location's number is 0 - set visible AND check neighbors using recursion
    if(g->board[row][col].numOfMines == 0)
    {
        g->hiddenTiles--; // Tile is not a mine
        g->board[row][col].isVisible = TRUE;

        // Check every neighbor's status
        clickTile(g, row, col+1);
        clickTile(g, row, col-1);
        clickTile(g, row-1, col-1);
        clickTile(g, row-1, col);
        clickTile(g, row-1, col+1);
        clickTile(g, row+1, col+1);
        clickTile(g, row+1, col);
        clickTile(g, row+1, col-1);
        return;
    }

    // Tile is a mine
    if(g->board[row][col].isMine)
    {
        g->isMineClicked = TRUE;
        return;
    }
}

/*
Function checks if the given location is located inside the given board's limits
@param g - pointer to the game board
@param row - row of the required location
@param col - col of the required location

@return - true if the given location is inside the board's limits, else return false.
*/
bool isLegal(GameBoard *g, int row, int col)
{
    return (row >= 0 && row < g->rows && col >= 0 && col < g->cols);
}


/*
Function marks/unmarks the tile in the given location as a flag (oposite of its current status)
@param g - pointer to the game board
@param row - row of the required location
@param col - col of the required location
*/
void flagTile(GameBoard *g, int row, int col)
{
    // If illegal location
    if(!isLegal(g, row, col))
        return;

    // If given location is already visible
    if(g->board[row][col].isVisible)
        return;

    g->board[row][col].isFlagged = !g->board[row][col].isFlagged;
}


/*
Function clears the screen and prints the board with all its tiles and their current status
@param g - pointer to the game board
@param cursorCoords - current player's location on the board. [0] defines the row and [1] defines the col
*/
void printBoard(GameBoard *g, int cursorCoords[2])
{
    clearScreen();
    printInstructions();
    printf("\n\tHidden Tiles: %d\n", g->hiddenTiles);
    printf("\tMines: %d\n\n", g->totalMines);

    int row = cursorCoords[0];
    int col = cursorCoords[1];

    for (int i = 0; i < g->rows; i++)
    {
        printf("\t"); // To set the board in a better location on the screen

        for (int j = 0; j < g->cols; j++)
        {
            // If it's the current player's location
            if(i == row && j == col)
            {
                char c[] = "  \0";

                // If the player is standing on a flagged tile
                if(g->board[i][j].isFlagged)
                    strcpy(c, " F\0");

                // If the player is standing on a visible tile
                if(g->board[i][j].numOfMines >= 0 && g->board[i][j].isVisible)
                    sprintf(c, " %d", g->board[i][j].numOfMines);

                // If the player is standing on a visible mine
                if(g->board[i][j].isMine && g->board[i][j].isVisible)
                    strcpy(c, " M\0");

                colorPrint(FG_Red, BG_Cyan, ATT_Def, c);
                continue;
            }

            // If tile is a visible mine (good when ending the game to reveal mines)
            if(g->board[i][j].isMine && g->board[i][j].isVisible)
            {
                colorPrint(FG_Green, BG_Red, ATT_Def, " M\0");
                continue;
            }

            // If tile is flagged (and the player isn't standing on it)
            if(g->board[i][j].isFlagged)
            {
                colorPrint(FG_Black, BG_Red, ATT_Def, " F\0");
                continue;
            }

            // If tile is visible and isn't a mine
            if(g->board[i][j].numOfMines >= 0 && g->board[i][j].isVisible)
            {
                char str[3];
                sprintf(str, " %d", g->board[i][j].numOfMines);
                colorPrint(FG_Black, BG_Magenta, ATT_Def, str);
                continue;
            }

            // Default hidden tile
            colorPrint(FG_Red, BG_White, ATT_Def, "  \0");
        }

        printf("\n");
    }
}

/*
Function sets all mines to visible. Good when ending a game (lose/win).
@param g - pointer to the game board
*/
void discoverMines(GameBoard *g)
{
    int rows = g->rows;
    int cols = g->cols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if(g->board[i][j].isMine)
                g->board[i][j].isVisible = TRUE;
}

/*
@param g - pointer to the game board
@return - TRUE if won, else return FALSE (doesn't mean it's a lose)
*/
bool isWin(GameBoard *g)
{
    return (g->hiddenTiles == 0);
}

/*
@param g - pointer to the game board
@return - TRUE if lost, else return FALSE (doesn't mean it's a win)
*/
bool isLose(GameBoard *g)
{
    return g->isMineClicked;
}

/*
Function to print the keys instructions
*/
void printInstructions()
{
    printf("-------------------------\n");
    printf("W - Move up\n");
    printf("S - Move down\n");
    printf("D - Move right\n");
    printf("A - Move left\n");

    printf("Space - Mark/Unmark flag\n");
    printf("Enter - Reveal tile\n");
    printf("-------------------------\n");
}

/*
Function to free all dynamic allocated pointers
*/
void freeBoard(GameBoard *g)
{
    for (int i = 0; i < g->rows; i++)
        free(g->board[i]);

    free(g->board);
}