#include "helper.h"

void clearConsole() {
    std::cout << "\033[:H\033[:J";
}

void swap(unsigned &x, unsigned &y) {
    unsigned temp = x;
    x = y;
    y = temp;
}

void copy(const char *from, char *to) {
    if (from == nullptr || to == nullptr) {
        return;
    }
    while (*from != '\0') {
        *to = *from;
        ++to;
        ++from;
    }
    *to = '\0';
}

void swap(char *str1, char *str2) {
    char temp[MAX_NICKNAME_LENGTH];
    copy(str1, temp);
    copy(str2, str1);
    copy(temp, str2);
}

unsigned **createBoard(size_t dim) {
    unsigned **board = new unsigned *[dim];
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

int compare(const char *str1, const char *str2) {
    if (str1 == nullptr || str2 == nullptr) {
        return -1;
    }
    while (*str1 != '\0' && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}

bool isValid(size_t dim) {
    return dim >= DIM_LOWER_BOUND && dim <= DIM_UPPER_BOUND;
}

char **allocateMatrix(size_t rows, size_t cols) {
    char** matrix = new char *[rows];
    for (size_t col = 0; col < rows; ++col) {
        matrix[col] = new char[cols];
    }
    return matrix;
}

void deallocateMatrix(char **matrix, size_t rows) {
    for (size_t row = 0; row < rows; ++row) {
        delete[] matrix[row];
    }
    delete[] matrix;
}

char toChar(size_t digit) {
    if (digit > 9) {
        return '0';
    }
    return (char) ('0' + digit);
}

size_t strlen(const char *str) {
    if (str == nullptr) {
        return 0;
    }
    size_t len = 0;
    while (str[len++] != '\0');
    return --len;
}

void concat(char *str1, const char *str2) {
    if (str1 == nullptr || str2 == nullptr) {
        return;
    }
    size_t len = strlen(str1);
    while (*str2 != '\0') {
        str1[len++] = *str2;
        ++str2;
    }
    str1[len] = '\0';
}