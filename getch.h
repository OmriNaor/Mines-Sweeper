// 208306068 - Omri Naor

#ifndef GETCH_H
#define GETCH_H
//hangs untill a key is pressed and returns its character, without waiting for '\n', and without echo (without printing the character to the screen).
char getch(void);
//same as getch, but also echos the character to the screen.
char getche(void);
#endif