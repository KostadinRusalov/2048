#include <iostream>
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
        std::cin.getline(command, COMMAND_LEN);
    }

    return 0;
}

void startGame() {

}

void showLeaderboard() {

}
