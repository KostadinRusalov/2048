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
#include "ui.h"

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
            invalidCommandMessage(command);
        }
        showMenu();
        std::cin.getline(command, COMMAND_LEN);
    }
    return 0;
}