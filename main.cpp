#include <iostream>

int DEFAULT_WIDTH = 6;

const char MOVE_UP = 'w';
const char MOVE_DOWN = 's';
const char MOVE_LEFT = 'a';
const char MOVE_RIGHT = 'd';

size_t merge(unsigned &x, unsigned &y) {
    y += x;
    x = 0;
    return y;
}

void swap(unsigned &x, unsigned &y) {
    unsigned temp = x;
    x = y;
    y = temp;
}

void shiftColumn(unsigned **&board, size_t dim, size_t colIdx, char cmd, unsigned &score, bool &changed) {
    if (board == nullptr || colIdx > dim || (cmd != MOVE_UP && cmd != MOVE_DOWN)) {
        return;
    }
    size_t start = cmd == MOVE_UP ? 0 : dim - 1;
    int direction = cmd == MOVE_UP ? 1 : -1;
    int emptySquares = 0;
    int lastNonZeroIdx = (int) start;

    for (size_t row = 1; row < dim; ++row) {
        size_t currIdx = start + direction * row;
        if (board[currIdx - direction][colIdx] == 0) {
            ++emptySquares;
        }
        if (board[currIdx][colIdx] == 0) {
            continue;
        }

        if (lastNonZeroIdx == -1 || board[currIdx][colIdx] != board[lastNonZeroIdx][colIdx]) {
            lastNonZeroIdx = (int) currIdx;
        } else if (board[currIdx][colIdx] == board[lastNonZeroIdx][colIdx]) {
            score += merge(board[currIdx][colIdx], board[lastNonZeroIdx][colIdx]);
            lastNonZeroIdx = -1;
            changed = true;
        }

        if (board[currIdx][colIdx] != 0 && emptySquares > 0) {
            lastNonZeroIdx = (int) currIdx - direction * emptySquares;
            swap(board[currIdx][colIdx], board[lastNonZeroIdx][colIdx]);
            --emptySquares;
            changed = true;
        }
    }
}

void shiftRow(unsigned **&board, size_t dim, size_t rowIdx, char cmd, unsigned &score, bool &changed) {
    if (board == nullptr || rowIdx > dim || (cmd != MOVE_LEFT && cmd != MOVE_RIGHT)) {
        return;
    }
    size_t start = cmd == MOVE_LEFT ? 0 : dim - 1;
    int direction = cmd == MOVE_LEFT ? 1 : -1;
    int emptySquares = 0;
    int lastNonZeroIdx = (int) start;

    for (size_t col = 1; col < dim; ++col) {
        size_t currIdx = start + direction * col;
        if (board[rowIdx][currIdx - direction] == 0) {
            ++emptySquares;
        }
        if (board[rowIdx][currIdx] == 0) {
            continue;
        }

        if (lastNonZeroIdx == -1 || board[rowIdx][currIdx] != board[rowIdx][lastNonZeroIdx]) {
            lastNonZeroIdx = (int) currIdx;
        } else if (board[rowIdx][currIdx] == board[rowIdx][lastNonZeroIdx]) {
            score += merge(board[rowIdx][currIdx], board[rowIdx][lastNonZeroIdx]);
            lastNonZeroIdx = -1;
            changed = true;
        }

        if (board[rowIdx][currIdx] != 0 && emptySquares > 0) {
            lastNonZeroIdx = (int) currIdx - direction * emptySquares;
            swap(board[rowIdx][currIdx], board[rowIdx][lastNonZeroIdx]);
            --emptySquares;
            changed = true;
        }
    }
}

size_t randomIdx(size_t count) {
    return rand() % count;
}

unsigned randomValue() {
    return 2 * (1 + rand() % 2);
}

size_t coordsToIdx(size_t row, size_t col) {
    return row * 10 + col;
}

size_t *idxToCoords(size_t idx) {
    auto *coords = new size_t[2];
    coords[1] = idx % 10;
    coords[0] = idx / 10;
    return coords;
}

unsigned *getEmptySquares(const unsigned **board, size_t dim, size_t &count) {
    auto *emptySquares = new unsigned[dim * dim];
    count = 0;
    for (size_t row = 0; row < dim; ++row) {
        for (size_t col = 0; col < dim; ++col) {
            if (board[row][col] == 0) {
                emptySquares[count++] = coordsToIdx(row, col);
            }
        }
    }
    return emptySquares;
}

bool availableMoves(const unsigned **board, size_t dim) {
    for (size_t row = 0; row < dim - 1; ++row) {
        for (size_t col = 0; col < dim - 1; ++col) {
            if (board[row][col] == board[row][col + 1]) {
                return true;
            }
            if (board[row][col] == board[row + 1][col]) {
                return true;
            }
        }
    }
    for (size_t row = 0; row < dim - 1; ++row) {
        if (board[row][dim - 1] == board[row + 1][dim - 1]) {
            return true;
        }
    }
    for (size_t col = 0; col < dim - 1; ++col) {
        if (board[dim - 1][col] == board[dim - 1][col + 1]) {
            return true;
        }
    }
    return false;
}

void addRandomValue(unsigned **&board, size_t dim, bool &finished) {
    size_t emptyCount;
    unsigned *emptySquares = getEmptySquares((const unsigned **) board, dim, emptyCount);
    size_t *coords = idxToCoords(emptySquares[randomIdx(emptyCount)]);
    board[coords[0]][coords[1]] = randomValue();
    delete[] emptySquares;
    delete[] coords;
    if (emptyCount == 1) {
        finished = !availableMoves((const unsigned **) board, dim);
    }
}

void moveBoard(unsigned **&board, size_t dim, char cmd, unsigned &score, bool &finished) {
    bool changed = false;
    if (cmd == MOVE_UP || cmd == MOVE_DOWN) {
        for (size_t colIdx = 0; colIdx < dim; ++colIdx) {
            shiftColumn(board, dim, colIdx, cmd, score, changed);
        }
    } else if (cmd == MOVE_LEFT || cmd == MOVE_RIGHT) {
        for (size_t rowIdx = 0; rowIdx < dim; ++rowIdx) {
            shiftRow(board, dim, rowIdx, cmd, score, changed);
        }
    }
    if (changed) {
        addRandomValue(board, dim, finished);
    }
}

unsigned **createBoard(size_t dim) {
    auto **board = new unsigned *[dim];
    for (size_t row = 0; row < dim; ++row) {
        board[row] = new unsigned[dim]{};
    }
    return board;
}

void deleteBoard(unsigned **board, size_t dim) {
    for (size_t row = 0; row < dim; ++row) {
        delete[] board[row];
    }
    delete[] board;
}

void clearConsole() {
    std::cout << "\033[:H\033[:J";
}

int digitCount(unsigned value) {
    int count = 1;
    while (value /= 10) {
        count++;
    }
    return count;
}

void printSpaces(int count) {
    while (count--) {
        std::cout << ' ';
    }
}

void printBoard(const unsigned **board, size_t dim, const char *nickname, unsigned score) {
    clearConsole();
    std::cout << nickname << "'s score: " << score << '\n';
    for (size_t row = 0; row < dim; ++row) {
        for (size_t col = 0; col < dim - 1; ++col) {
            std::cout << board[row][col];
            printSpaces(DEFAULT_WIDTH - digitCount(board[row][col]));
        }
        std::cout << board[row][dim - 1] << '\n';
    }
}

void startGame() {
    const size_t DEFAULT_NICKNAME_LENGTH = 20;
    const size_t LOWER_BOUND = 4, UPPER_BOUND = 10;
    srand(time(nullptr));
    clearConsole();

    char nickname[DEFAULT_NICKNAME_LENGTH];
    std::cout << "enter nickname: ";
    std::cin >> nickname;

    size_t dim;
    std::cout << "enter dimension (between 4 and 10): ";
    std::cin >> dim;
    while (dim < LOWER_BOUND || dim > UPPER_BOUND) {
        std::cout << "invalid dimension\n";
        std::cout << "enter dimension (between 4 and 10): ";
        std::cin >> dim;
    }

    unsigned score = 0;
    unsigned **board = createBoard(dim);
    bool finished = false;
    addRandomValue(board, dim, finished);
    addRandomValue(board, dim, finished);
    printBoard((const unsigned **) board, dim, nickname, score);

    char cmd;
    std::cin >> cmd;

    while (cmd != 'q') {
        moveBoard(board, dim, cmd, score, finished);
        printBoard((const unsigned **) board, dim, nickname, score);
        if (finished) {
            break;
        }
        std::cin >> cmd;
    }

    std::cout << "well played " << nickname << "\nyour score is " << score;
    deleteBoard(board, dim);
}


int main() {
    startGame();
    return 0;
}