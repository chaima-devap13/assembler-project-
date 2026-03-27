#include<stdio.h>
#include"error.h"
#include<stdlib.h>

void errorInvalidA(char *line, int lineNumber) {
    printf("Error at line %d: Invalid A-instruction -> %s\n", lineNumber, line);
    exit(1);
}

void errorInvalidComp(char *comp, int lineNumber) {
    printf("Error at line %d: Invalid comp field -> %s\n", lineNumber, comp);
    exit(1);
}

void errorInvalidDest(char *dest, int lineNumber) {
    printf("Error at line %d: Invalid dest field -> %s\n", lineNumber, dest);
    exit(1);
}

void errorInvalidJump(char *jump, int lineNumber) {
    printf("Error at line %d: Invalid jump field -> %s\n", lineNumber, jump);
    exit(1);
}

void errorDuplicateLabel(char *label, int lineNumber) {
    printf("Error at line %d: Duplicate label -> %s\n", lineNumber, label);
    exit(1);
}