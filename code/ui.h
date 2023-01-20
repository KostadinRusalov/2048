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

const int IGNORE_COUNT = 256;
const char IGNORE_DEL = '\n';

const int COMMAND_LEN = 12;

const char INVALID_COMMAND_MESSAGE[] = "invalid command!\n";

const char START_GAME_COMMAND[] = "start game";
const char LEADERBOARD_COMMAND[] = "leaderboard";
const char QUIT_COMMAND[] = "quit";

const char QUIT = 'q';

const char START_GAME_COMMAND_N[] = "1";
const char LEADERBOARD_COMMAND_N[] = "2";
const char QUIT_COMMAND_N[] = "3";

const char COMMAND_MENU[] = "1. start game\n"
                            "2. leaderboard\n"
                            "3. quit";

const char ENTER_NICKNAME_MESSAGE[] = "enter nickname: ";
const char INVALID_NICKNAME_MESSAGE[] = "nickname must be less than 15 characters!\n";

const char ENTER_DIMENSION_MESSAGE[] = "enter dimension (between 4 and 10): ";
const char INVALID_DIMENSION_MESSAGE[] = "invalid dimension!\n";


void showMenu();

void clearInput();

size_t enterDimension();

void invalidCommandMessage();

void emptyLeaderboardMessage();

bool isQuit(const char *);

void enterNickname(char *);

bool isStartGame(const char *);

bool isLeaderboard(const char *);

void wellPlayed(const char *, unsigned);

void printScores(const char **, const unsigned *, size_t);

void printBoard(const unsigned **, size_t, const char *, unsigned);

#endif
