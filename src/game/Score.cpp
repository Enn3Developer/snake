#include "Score.h"

#include <cstdlib>
#include <cstring>
#include <curses.h>

int power(int base, int exponent) {
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result = result * base;
    }

    return result;
}

int charToInt(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return -1;
    }
}

int stringToInt(const char *str) {
    int len = strlen(str);
    int number = 0;

    for (int i = 0; i < len; i++) {
        char c = str[i];
        int digit = charToInt(c);
        if (digit == -1) continue;
        number += digit * power(10, len - i - 1);
    }

    return number;
}

void intToString(int number, char *str) {
    sprintf(str, "%d", number);
}

Score::Score() {
    this->score = 0;
    this->level = 0;
}

void Score::toString(char *str) {
    char score[BUFFER_LEN] = {};
    char level[BUFFER_LEN] = {};

    intToString(this->score, score);
    intToString(this->level, level);

    strcat(str, score);
    str[strlen(score)] = ';';
    strcat(str, level);
}

void Score::fromString(const char *str) {
    char score[BUFFER_LEN] = {};
    char level[BUFFER_LEN] = {};
    int len = strlen(str);
    int splitPosition = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == ';') {
            splitPosition = i;
        }
    }

    // BUFFER OVERFLOW CHECK
    if (splitPosition >= BUFFER_LEN - 1 || len - splitPosition >= BUFFER_LEN - 1 || len == splitPosition - 1) {
        endwin();
        printf("BUFFER OVERFLOW CAUGHT IN TIME\n");
        fflush(stdout);
        exit(1);
    }

    for (int i = 0; i < splitPosition; i++) {
        score[i] = str[i];
    }

    for (int i = splitPosition + 1; i < len; i++) {
        level[i - splitPosition - 1] = str[i];
    }

    this->score = stringToInt(score);
    this->level = stringToInt(level);
}
