/**
 *
 * Solution to course project # 4
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2022/2023
 *
 * @author Kostadin Rusalov
 * @idnumber 2MI0600244
 * @compiler GCC
 *
 * header file with ui consts and functions
 *
*/
#include <iostream>

#ifndef INC_2048_UI_H
#define INC_2048_UI_H

const int COMMAND_LEN = 12;

void clearConsole();

void clearInput();

void showMenu();

void startGame();

void showLeaderboard();

void invalidCommandMessage(const char *);

bool isQuit(const char *);

bool isStartGame(const char *);

bool isLeaderboard(const char *);

#endif