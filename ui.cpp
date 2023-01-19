#include "ui.h"
#include "helper.h"

void showMenu() {
    std::cout << COMMAND_MENU << std::endl;
}

bool isQuit(const char *command) {
    return compare(command, QUIT_COMMAND) == 0 || compare(command, QUIT_COMMAND_N) == 0;
}

bool isStartGame(const char *command) {
    return compare(command, START_GAME_COMMAND) == 0 || compare(command, START_GAME_COMMAND_N) == 0;
}

bool isLeaderboard(const char *command) {
    return compare(command, LEADERBOARD_COMMAND) == 0 || compare(command, LEADERBOARD_COMMAND_N) == 0;
}