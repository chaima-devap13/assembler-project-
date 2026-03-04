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
    char *eq = strchr(line, '=');
    char *sc = strchr(line, ';');

    if (eq) {
        strncpy(dest, line, eq - line);
        dest[eq - line] = '\0';
        line = eq + 1;
    } else strcpy(dest, "null");

    if (sc) {
        strncpy(comp, line, sc - line);
        comp[sc - line] = '\0';
        strcpy(jump, sc + 1);
    } else {
        strcpy(comp, line);
        strcpy(jump, "null");
    }
}