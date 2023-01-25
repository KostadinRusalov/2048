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
#include "gameLogic.h"
#include "leaderboardLogic.h"

int BOARD_TILE_WIDTH = 6;

const char START_GAME_COMMAND[] = "start game";
const char LEADERBOARD_COMMAND[] = "leaderboard";
const char QUIT_COMMAND[] = "quit";

const char START_GAME_COMMAND_N[] = "1";
const char LEADERBOARD_COMMAND_N[] = "2";
const char QUIT_COMMAND_N[] = "3";

const char COMMAND_MENU[] = "1. start game\n"
                            "2. leaderboard\n"
                            "3. quit";

const char ENTER_NICKNAME_MESSAGE[] = "enter nickname: ";
const char INVALID_NICKNAME_MESSAGE[] = "nickname cannot be more than 15 characters or contain spaces!\n";

const char ENTER_DIMENSION_MESSAGE[] = "enter dimension (between 4 and 10): ";
const char INVALID_DIMENSION_MESSAGE[] = "invalid dimension!\n";

void clearConsole() {
    std::cout << "\033[:H\033[:J";
}

void showMenu() {
    std::cout << COMMAND_MENU << std::endl;
}

void clearInput() {
    const int IGNORE_COUNT = 256;
    const char IGNORE_DEL = '\n';
    if (std::cin.fail()) {
        std::cin.clear();
    }
    std::cin.ignore(IGNORE_COUNT, IGNORE_DEL);
}

void invalidCommandMessage(const char *command) {
    std::cout << command << " is invalid command!" << std::endl;
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
    std::cout << "well played " << nickname << "!\nyour score is " << score << std::endl << std::endl;
}

void emptyLeaderboardMessage() {
    std::cout << "leaderboard is empty" << std::endl;
}

void printScores(const char **nicknames, const unsigned *scores, size_t count) {
    for (size_t idx = 0; idx < count; ++idx) {
        std::cout << idx + 1 << ". " << nicknames[idx] << "'s high score: " << scores[idx] << '\n';
    }
    std::cout << std::endl;
}

bool isValid(const char *nickname) {
    if (nickname == nullptr) {
        return false;
    }
    while (*nickname != '\0') {
        if (*nickname == ' ') {
            return false;
        }
        ++nickname;
    }
    return true;
}

void enterNickname(char *nickname) {
    std::cout << ENTER_NICKNAME_MESSAGE;
    std::cin.getline(nickname, MAX_NICKNAME_LENGTH);

    while (std::cin.fail() || !isValid(nickname)) {
        std::cout << INVALID_NICKNAME_MESSAGE;
        std::cout << ENTER_NICKNAME_MESSAGE;
        clearInput();
        std::cin.getline(nickname, MAX_NICKNAME_LENGTH);
    }
}

size_t enterDimension() {
    std::cout << ENTER_DIMENSION_MESSAGE;
    size_t dim;
    std::cin >> dim;

    while (std::cin.fail() || !isValid(dim)) {
        std::cout << INVALID_DIMENSION_MESSAGE;
        std::cout << ENTER_DIMENSION_MESSAGE;
        clearInput();
        std::cin >> dim;
    }

    return dim;
}

void printBoard(const unsigned **board, size_t dim, const char *nickname, unsigned score) {
    clearConsole();
    std::cout << nickname << "'s score: " << score << '\n';

    for (size_t row = 0; row < dim; ++row) {
        for (size_t col = 0; col < dim - 1; ++col) {
            unsigned tile = board[row][col];
            int digits = digitCount(tile);

            // a known bug
            if (digits >= BOARD_TILE_WIDTH) {
                BOARD_TILE_WIDTH += 2;
            }

            std::cout << tile;
            printSpaces(BOARD_TILE_WIDTH - digits);
        }
        std::cout << board[row][dim - 1] << std::endl;
    }
}

void startGame() {
    const char QUIT = 'q';

    srand(time(nullptr));
    clearConsole();

    char nickname[MAX_NICKNAME_LENGTH];
    enterNickname(nickname);

    size_t dim = enterDimension();

    unsigned score = 0;
    bool finished = false;

    // initialize board with two random tiles
    unsigned **board = createBoard(dim);
    addRandomTile(board, dim, finished);
    addRandomTile(board, dim, finished);

    printBoard((const unsigned **) board, dim, nickname, score);

    char command;
    std::cin >> command;

    while (command != QUIT) {
        moveBoard(board, dim, command, score, finished);
        printBoard((const unsigned **) board, dim, nickname, score);
        if (finished) {
            break;
        }
        clearInput();
        std::cin >> command;
    }

    appendLeaderboard(dim, nickname, score);
    deleteBoard(board, dim);
    wellPlayed(nickname, score);
}

void showLeaderboard() {
    clearConsole();
    size_t dim = enterDimension();
    size_t count = 0;

    char **nicknames = allocateMatrix(MAX_NICKNAMES_SCORES_COUNT, MAX_NICKNAME_LENGTH);
    unsigned *scores = new unsigned[MAX_NICKNAMES_SCORES_COUNT];

    getNicknamesScores(dim, nicknames, scores, count);

    if (count == 0) {
        emptyLeaderboardMessage();
    } else {
        printScores((const char **) nicknames, (const unsigned *) scores, count);
    }
    std::cout << std::endl;
    deallocateMatrix(nicknames, MAX_NICKNAMES_SCORES_COUNT);
    delete[] scores;
}