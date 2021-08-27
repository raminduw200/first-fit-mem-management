#include <stdio.h>

/*
 * Text formatting such as text bolding and coloring
 */

// Method to bold text, errors
void printb(char* string_){
    printf("\e[1m%s\e[0m", string_);
};

void printRed(char* string_){
    printf("\\033[1;31m%s\\033[0m", string_);
}

void printGreen(char* string_) {
    printf("\\033[0;32m%s", string_);
}

void printYellow(char* string_) {
    printf("\\033[0;33m%s\033[0m", string_);
}

void printBlue(char* string_) {
    printf("\\033[0;34m%s\033[0m", string_);
}

void printPurple(char* string_) {
    printf("\\033[0;35m%s\033[0m", string_);
}

void printCyan(char* string_) {
    printf("\\033[0;36m%s\033[0m", string_);
}

void printWhite(char* string_) {
    printf("\\033[0;37m%s\033[0m", string_);
}
