#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

typedef enum {
    LABEL,
    VARIABLE,
    PREDEFINED
} SymbolType;

void printSymbolTable();
void initSymbolTable();
void addSymbol(char *symbol, int address,SymbolType type);
int containsSymbol(char *symbol);
int getAddress(char *symbol);
//Caesar Cipher //Caesar Cipher
#endif