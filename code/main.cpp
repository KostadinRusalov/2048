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
 * main game file
 *
*/
#include <iostream>
#include "leaderboardLogic.h"
#include "gameLogic.h"
#include "helper.h"
#include "ui.h"

void startGame();

void showLeaderboard();

int main() {
    clearConsole();
    showMenu();

    char command[COMMAND_LEN];
    std::cin.getline(command, COMMAND_LEN);

    while (!isQuit(command)) {
        if (isStartGame(command)) {
            startGame();
        } else if (isLeaderboard(command)) {
            showLeaderboard();
        } else {
            invalidCommand();
        }
        showMenu();
        std::cin.ignore(IGNORE_COUNT,IGNORE_DEL);
        std::cin.getline(command, COMMAND_LEN);
    }

    return 0;
}

void startGame() {
    srand(time(nullptr));
    clearConsole();

    char nickname[MAX_NICKNAME_LENGTH];
    std::cout << ENTER_NICKNAME_MESSAGE;
    std::cin >> nickname;

    size_t dim;
    std::cout << ENTER_DIMENSION_MESSAGE;
    std::cin >> dim;

    while (dim < DIM_LOWER_BOUND || dim > DIM_UPPER_BOUND) {
        std::cout << INVALID_DIMENSION_MESSAGE;
        std::cout << ENTER_DIMENSION_MESSAGE;
        std::cin >> dim;
    }

    // initialize board
    unsigned score = 0;
    bool finished = false;
    unsigned **board = createBoard(dim);
    addRandomTile(board, dim, finished);
    addRandomTile(board, dim, finished);
    printBoard((const unsigned **) board, dim, nickname, score);

    char command;
    std::cin >> command;

    while (command != 'q') {
        moveBoard(board, dim, command, score, finished);
        printBoard((const unsigned **) board, dim, nickname, score);
        if (finished) {
            break;
        }
        std::cin.ignore(IGNORE_COUNT,IGNORE_DEL);
        std::cin >> command;
    }

    appendLeaderboard(dim, nickname, score);
    deleteBoard(board, dim);
    wellPlayed(nickname, score);
}

void showLeaderboard() {
    clearConsole();
    size_t dim;
    std::cout << ENTER_DIMENSION_MESSAGE;
    std::cin >> dim;

    while (dim < DIM_LOWER_BOUND || dim > DIM_UPPER_BOUND) {
        std::cout << INVALID_DIMENSION_MESSAGE;
        std::cout << ENTER_DIMENSION_MESSAGE;
        std::cin >> dim;
    }

    size_t count = 0;
    char **nicknames = allocateMatrix(MAX_NICKNAMES_SCORES_COUNT, MAX_NICKNAME_LENGTH);
    unsigned *scores = new unsigned[MAX_NICKNAMES_SCORES_COUNT];

    getNicknamesScores(dim, nicknames, scores, count);

    if (count == 0) {
        emptyLeaderboard();
    } else {
        printScores((const char **) nicknames, (const unsigned *) scores, count);
    }

    deallocateMatrix(nicknames, MAX_NICKNAMES_SCORES_COUNT);
    delete[] scores;
}