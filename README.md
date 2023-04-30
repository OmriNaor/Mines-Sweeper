# C Project: Minesweeper

## Introduction

This project is an implementation of the classic Minesweeper game in C. It features a customizable board size and adjustable difficulty levels, making it a fun and challenging game for players of all skill levels.

## About

A typical Minesweeper game with the standard rules. Reveal all tiles while avoiding the mines.

## Structure

- `game.c` - Main function definition. Manages the game and the user's inputs.
- `mineSweeper.c` - Creates the board and populates the mines randomly. Additionally, prints the board.
- `getch.c` - Gets and returns a char input from the user without the requirement of pressing ENTER to finish.
- `colorPrint.c` - Prints to the screen a given String with the given color (enum). Same as printf but with a color (String/Background).

## The Algorithm

The program starts by asking the user to enter the board dimensions when the minimum is a 4x4 board and the maximum is 20x20. Additionally, asks the user for difficulty (Easy/Medium/Hard).

The algorithm checks if the given values are legal, otherwise sets default values.

Lastly, the algorithm populates the mines around the board depending on the given difficulty (the more difficult the higher mines percentage).

The main function uses a while loop and constantly asks the user for their input. Additionally, the main functions keeps drawing the updated board and checking whether the game is over (lose/win).

## Controls

- A - Move left
- D - Move right
- S - Move down
- W - Move up
- Space - (un)mark a tile with a flag
- Enter - Reveal a tile

## Getting Started

To compile and run the project, follow these steps:

1. Clone the repository or download the source code.
2. Navigate to the project directory.
3. Compile the project using a C compiler (e.g., gcc): `gcc -o minesweeper game.c mineSweeper.c getch.c colorPrint.c`
4. Run the compiled executable: `./minesweeper`

## Examples

![mid-game](https://user-images.githubusercontent.com/106623821/206722413-c9eb5425-80e6-43b4-aa7e-93c21929627f.jpg)
![win](https://user-images.githubusercontent.com/106623821/206722426-85d82068-51f9-4b00-8e59-d8e322c7d943.jpg)
![lose](https://user-images.githubusercontent.com/106623821/206722430-48ee21a5-8ab8-442f-aaeb-4d92f9db0bd9.jpg)
