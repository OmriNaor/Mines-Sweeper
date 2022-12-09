# Java Project: Minesweeper

## About

A typical Minewseeper game with the typical rules. Reveal all tiles while avoiding the mines.


## Structure

- `main.c` - Main function definition. Manages the game and the user's inputs.
- `mineSweeper.c` - Creates the the board and populates the mines randomly. Additionally prints the board.
- `getch.c` - Gets and returns a char input from the user without the requirement of pressing ENTER to finish.

## The Algorithm

The program starts by asking the user to enter the board dimensions when the minimum is a 4x4 board and the maximum is 20x20. Additionally, asks the user for difficulty (Easy/Medium/Hard).

The algorithm checks if the given values are legal, otherwise sets default values.

Lastly, the algorithm populates the mines around the board depending on the given difficulty (the more difficult the higher mines percentage).

The main function uses a while loop and constantly asks the user for his input. Additionally, the main functions keeps drawing the updated board and checking whether the game is over (lose/win).


## Examples



![mid-game](https://user-images.githubusercontent.com/106623821/206722413-c9eb5425-80e6-43b4-aa7e-93c21929627f.jpg)
![win](https://user-images.githubusercontent.com/106623821/206722426-85d82068-51f9-4b00-8e59-d8e322c7d943.jpg)
![lose](https://user-images.githubusercontent.com/106623821/206722430-48ee21a5-8ab8-442f-aaeb-4d92f9db0bd9.jpg)



