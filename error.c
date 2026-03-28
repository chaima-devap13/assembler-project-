#include<stdio.h>
#include"error.h"
#include<stdlib.h>
  int errorCount = 0; // Global variable to track the number of errors
  // Error handling functions for different types of errors encountered during assembly parsing and encoding. Each function prints a specific error message along with the line number and the offending line of code, and increments the global error count.
void errorInvalidA(char *line, int lineNumber) {
    printf("Error at line %d: Invalid A-instruction -> %s\n", lineNumber, line);
    errorCount++; // Increment the error count for each invalid A-instruction
}

void errorInvalidComp(char *comp, int lineNumber, char *line) {
    printf("Error at line %d: Invalid comp '%s'\n", lineNumber, comp);
    printf("Expected valid comp like: D, A, M, D+M, D-A...\n");
    printf("Line: %s\n\n", line);// Print the line of code that caused the error for better debugging
    errorCount++;
}

void errorInvalidDest(char *dest, int lineNumber, char *line) {
    printf("Error at line %d: Invalid dest '%s'\n", lineNumber, dest);
    printf("Expected: M, D, MD, A, AM, AD, AMD\n");
    printf("Line: %s\n\n", line);
    errorCount++;
}

void errorInvalidJump(char *jump, int lineNumber, char *line) {
    printf("Error at line %d: Invalid jump field -> %s\n", lineNumber, jump);
    printf("Expected: JGT, JEQ, JGE, JLT, JNE, JLE, JMP\n");
    printf("Line: %s\n\n", line);
    errorCount++;
}

void errorDuplicateLabel(char *label, int lineNumber) {
    printf("Error at line %d: Duplicate label -> %s\n", lineNumber, label);
    errorCount++;
}
void errorInvalidSyntax(char *line, int lineNumber) {
    printf("Error at line %d: Invalid syntax -> %s\n", lineNumber, line);
    errorCount++;
}