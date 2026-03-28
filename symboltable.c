#include <stdio.h>
#include <string.h>
#include "symboltable.h"

#define MAX_SYMBOLS 1000
// The symbol table is implemented as an array of Symbol structures, where each Symbol contains a symbol name and its corresponding address. The table supports adding new symbols, checking for the existence of a symbol, and retrieving the address associated with a symbol. The initSymbolTable function initializes the table with predefined symbols for registers and memory-mapped I/O. The printSymbolTable function is used for debugging purposes to display the contents of the symbol table after processing the assembly file.
typedef struct {
    char symbol[50];
    int address;
} Symbol;

Symbol table[MAX_SYMBOLS];
int symbolCount = 0;
 // Initializes the symbol table with predefined symbols for registers (R0 to R15) and memory-mapped I/O addresses (SCREEN and KBD). This function is called at the beginning of the assembly process to ensure that these standard symbols are available for use in A-instructions without needing to be defined in the assembly code.
void initSymbolTable() {
    for (int i = 0; i < 16; i++) {
        char r[5];
        sprintf(r, "R%d", i);
        addSymbol(r, i);
    }
    addSymbol("SCREEN", 16384);
    addSymbol("KBD", 24576);
}
// Adds a new symbol to the symbol table with the specified name and address. This function is used during the first pass of the assembly process to add label definitions (L_COMMAND) to the symbol table, as well as during the second pass to add variable symbols encountered in A_COMMANDs that are not already in the table.
void addSymbol(char *symbol, int address) {
    strcpy(table[symbolCount].symbol, symbol);
    table[symbolCount].address = address;
    symbolCount++;
}
// Checks if a symbol exists in the symbol table. This function is used during the second pass to determine if a symbol in an A_COMMAND is already defined (either as a label or a predefined symbol) or if it needs to be added as a new variable symbol.
int containsSymbol(char *symbol) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(table[i].symbol, symbol) == 0)
            return 1;
    }
    return 0;
}
// Retrieves the address associated with a symbol from the symbol table. This function is used during the second pass to resolve symbols in A_COMMANDs to their corresponding addresses, whether they are predefined symbols, labels, or variable symbols.
int getAddress(char *symbol) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(table[i].symbol, symbol) == 0)
            return table[i].address;
    }
    return -1;
}
// Prints the contents of the symbol table to the console. This function is useful for debugging purposes to verify that symbols are being added correctly during the first pass and to see the final state of the symbol table after processing the assembly file.
void printSymbolTable() {

    printf("\n===== SYMBOL TABLE =====\n");

    for (int i = 0; i < symbolCount; i++) {
        printf("%-10s -> %d\n", table[i].symbol, table[i].address);
    }

    printf("========================\n\n");
}