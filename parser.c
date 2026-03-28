#include <string.h>
#include <stdio.h>
#include "parser.h"

int commandType(char *line) {
    if (line[0] == '@') return A_COMMAND;
    if (line[0] == '(') return L_COMMAND;
    return C_COMMAND;
}

void getSymbol(char *line, char *symbol) {
    if (line[0] == '@') {
        strcpy(symbol, line + 1);
    } else {
        sscanf(line, "(%[^)])", symbol);
    }
}

void parseC(char *line, char *dest, char *comp, char *jump) {

    char temp[256];
    strcpy(temp, line);   

    char *eq = strchr(temp, '=');
    char *sc = strchr(temp, ';');

    if (eq) {
        *eq = '\0';
        strcpy(dest, temp);
        strcpy(comp, eq + 1);
    } else {
        strcpy(dest, "null");
        strcpy(comp, temp);
    }

    if (sc) {
        *sc = '\0';
        strcpy(comp, eq ? eq + 1 : temp);
        strcpy(jump, sc + 1);
    } else {
        strcpy(jump, "null");
    }
}