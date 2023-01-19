#include <iostream>
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
            std::cout << INVALID_COMMAND_MESSAGE << std::endl;
        }
        showMenu();
        std::cin.clear();
        std::cin.ignore();
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
        std::cin >> command;
    }
    deleteBoard(board, dim);
    std::cout << "well played " << nickname << "!\nyour score is " << score << std::endl;
}

void showLeaderboard() {

}
