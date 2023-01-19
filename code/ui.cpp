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
 * file for ui functions
 *
*/
#include "ui.h"
#include "helper.h"

void showMenu() {
    std::cout << COMMAND_MENU << std::endl;
}

void invalidCommand() {
    std::cout << INVALID_COMMAND_MESSAGE;
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

void wellPlayed(const char *nickname, unsigned score) {
    std::cout << "well played " << nickname << "!\nyour score is " << score << std::endl;
}

void emptyLeaderboard() {
    std::cout << "leaderboard is empty" << std::endl;
}

void printScores(const char **nicknames, const unsigned *scores, size_t count) {
    for (size_t idx = 0; idx < count; ++idx) {
        std::cout << idx + 1 << ". " << nicknames[idx] << "'s high score: " << scores[idx] << '\n';
    }
    std::cout << std::endl;
}