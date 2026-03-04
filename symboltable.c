#include <stdio.h>
#include <string.h>
#include "symboltable.h"

#define MAX_SYMBOLS 1000

typedef struct {
    char symbol[50];
    int address;
} Symbol;

Symbol table[MAX_SYMBOLS];
int symbolCount = 0;

void initSymbolTable() {
    for (int i = 0; i < 16; i++) {
        char r[5];
        sprintf(r, "R%d", i);
        addSymbol(r, i);
    }
    addSymbol("SCREEN", 16384);
    addSymbol("KBD", 24576);
}

void addSymbol(char *symbol, int address) {
    strcpy(table[symbolCount].symbol, symbol);
    table[symbolCount].address = address;
    symbolCount++;
}

int containsSymbol(char *symbol) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(table[i].symbol, symbol) == 0)
            return 1;
    }
    return 0;
}

int getAddress(char *symbol) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(table[i].symbol, symbol) == 0)
            return table[i].address;
    }
    return -1;
}
void printSymbolTable() {

    printf("\n===== SYMBOL TABLE =====\n");

    for (int i = 0; i < symbolCount; i++) {
        printf("%-10s -> %d\n", table[i].symbol, table[i].address);
    }

    printf("========================\n\n");
}