#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

void printSymbolTable();
void initSymbolTable();
void addSymbol(char *symbol, int address);
int containsSymbol(char *symbol);
int getAddress(char *symbol);

#endif