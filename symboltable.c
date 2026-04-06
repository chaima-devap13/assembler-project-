#include <stdio.h>
#include <string.h>
#include "symboltable.h"

#define MAX_SYMBOLS 1000
// The symbol table is implemented as an array of Symbol structures, where each Symbol contains a symbol name and its corresponding address. The table supports adding new symbols, checking for the existence of a symbol, and retrieving the address associated with a symbol. The initSymbolTable function initializes the table with predefined symbols for registers and memory-mapped I/O. The printSymbolTable function is used for debugging purposes to display the contents of the symbol table after processing the assembly file.

typedef struct {
    char symbol[50];
    int address;
    SymbolType type; // Optional: can be used to differentiate between labels and variables if needed
} Symbol;

Symbol table[MAX_SYMBOLS];
int symbolCount = 0;
 // Initializes the symbol table with predefined symbols for registers (R0 to R15) and memory-mapped I/O addresses (SCREEN and KBD). This function is called at the beginning of the assembly process to ensure that these standard symbols are available for use in A-instructions without needing to be defined in the assembly code.
void initSymbolTable() {

    symbolCount = 0; 

    for (int i = 0; i < 16; i++) {
        char r[5];
        sprintf(r, "R%d", i);
        addSymbol(r, i, PREDEFINED);
    }

    addSymbol("SCREEN", 16384, PREDEFINED);
    addSymbol("KBD", 24576, PREDEFINED);
}
// Adds a new symbol to the symbol table with the specified name and address. This function is used during the first pass of the assembly process to add label definitions (L_COMMAND) to the symbol table, as well as during the second pass to add variable symbols encountered in A_COMMANDs that are not already in the table.
void addSymbol(char *symbol, int address,SymbolType type) {
    strcpy(table[symbolCount].symbol, symbol);
    table[symbolCount].address = address;
    table[symbolCount].type = type;
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
char* typeToString(SymbolType type) {
    switch(type) {
        case LABEL: return "label";
        case VARIABLE: return "variable";
        case PREDEFINED: return "predefined";
        default: return "unknown";
    }
} //ndfhp fkdlpd
// Prints the contents of the symbol table to the console. This function is useful for debugging purposes to verify that symbols are being added correctly during the first pass and to see the final state of the symbol table after processing the assembly file.

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"

#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[96m"

// ...existing code...

static void printTruncated(const char *text, int width) {
    char buf[64];
    if ((int)strlen(text) > width) {
        snprintf(buf, sizeof(buf), "%.s", text); // placeholder
        snprintf(buf, sizeof(buf), "%.*s...", width - 3, text);
    } else {
        snprintf(buf, sizeof(buf), "%s", text);
    }
    printf("%-*s", width, buf);
}

void printSymbolTable() {
    printf("\n%s%s╔═════════════════════════════════════════════════════╗%s\n", CYAN, BOLD, RESET);
    printf("%s%s║                          SYMBOL TABLE VIEW          ║%s\n", CYAN, BOLD, RESET);
    printf("%s╠═════════════════════════════════════════════════════╣%s\n", CYAN, RESET);

    printf("%s║ Total Symbols: %-3d                                  ║%s\n", MAGENTA, symbolCount, RESET);

    printf("%s╠═════╦══════════════════════╦═════════╦══════════════╣%s\n", CYAN, RESET);
    printf("%s║ ID  ║ Name                 ║ Address ║ Type         ║%s\n", BOLD, RESET);
    printf("%s╠═════╬══════════════════════╬═════════╬══════════════╣%s\n", CYAN, RESET);
 //ndfhp fkdlpd
    for (int i = 0; i < symbolCount; i++) {
        char *color;
        char *typeStr = typeToString(table[i].type);

        if (table[i].type == PREDEFINED)
            color = BLUE;
        else if (table[i].type == LABEL)
            color = GREEN;
        else
            color = YELLOW;

        printf("%s║ %3d ║ ", CYAN, i);
        printTruncated(table[i].symbol, 20);
        printf(" ║ %7d ║ ", table[i].address);
        printf("%s", color);
        printTruncated(typeStr, 12);
        printf("%s ║\n", RESET);
    }

    printf("%s╠═════════════════════════════════════════════════════╣%s\n", CYAN, RESET);
    printf("%s║ %-82s ║%s\n", DIM, "End of Table", RESET);
    printf("%s╚═════════════════════════════════════════════════════╝%s\n\n", CYAN, RESET);
}

// ...existing code...

