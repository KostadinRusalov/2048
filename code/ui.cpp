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

int BOARD_TILE_WIDTH = 6;

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

void printBoard(const unsigned **board, size_t dim, const char *nickname, unsigned score) {
    clearConsole();
    std::cout << nickname << "'s score: " << score << '\n';
    for (size_t row = 0; row < dim; ++row) {
        for (size_t col = 0; col < dim - 1; ++col) {
            unsigned tile = board[row][col];
            int digits = digitCount(tile);

            if (digits >= BOARD_TILE_WIDTH) {
                BOARD_TILE_WIDTH += 2;
            }

            std::cout << tile;
            printSpaces(BOARD_TILE_WIDTH - digits);
        }
        std::cout << board[row][dim - 1] << std::endl;
    }
}