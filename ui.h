#include <iostream>

#ifndef INC_2048_UI_H
#define INC_2048_UI_H

const int COMMAND_LEN = 12;

const char INVALID_COMMAND_MESSAGE[] = "invalid command!";

const char START_GAME_COMMAND[] = "start game";
const char LEADERBOARD_COMMAND[] = "leaderboard";
const char QUIT_COMMAND[] = "quit";

const char START_GAME_COMMAND_N[] = "1";
const char LEADERBOARD_COMMAND_N[] = "2";
const char QUIT_COMMAND_N[] = "3";

const char COMMAND_MENU[] = "1. start game\n"
                            "2. leaderboard\n"
                            "3. quit";

void showMenu();

bool isQuit(const char*);
bool isStartGame(const char*);
bool isLeaderboard(const char*);

#endif //INC_2048_UI_H
