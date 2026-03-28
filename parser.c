#include <string.h>
#include <stdio.h>
#include "parser.h"

int commandType(char *line) {
    if (line[0] == '@') return A_COMMAND; // If the line starts with '@', it is an A-instruction (A_COMMAND), which is used to set the value of the A register or to reference a symbol. The function checks the first character of the line and returns the corresponding command type.
    if (line[0] == '(') return L_COMMAND; // If the line starts with '(', it is a label declaration (L_COMMAND), which defines a label that can be used as a symbol in A-instructions. The function checks the first character of the line and returns the corresponding command type.
    return C_COMMAND;
}

void getSymbol(char *line, char *symbol) {
    if (line[0] == '@') {
        strcpy(symbol, line + 1);
    } else {
        sscanf(line, "(%[^)])", symbol);// For L_COMMAND, extract the label name by reading the characters between '(' and ')'. The sscanf function is used to parse the line and store the label name in the symbol variable.
    }
}
// The parseC function takes a C-instruction line and extracts the dest, comp, and jump components. It uses string manipulation to identify the positions of '=' and ';' characters, which separate the different parts of the C-instruction. The function fills the dest, comp, and jump variables based on the syntax of the C-instruction, allowing for later encoding into binary.
void parseC(char *line, char *dest, char *comp, char *jump) {

    char temp[256];
    strcpy(temp, line);   

    char *eq = strchr(temp, '=');// Find the position of the '=' character in the line, which separates the dest and comp parts of the C-instruction. The strchr function is used to locate the first occurrence of '=' in the temp string, and it returns a pointer to that position. If '=' is not found, eq will be NULL.
    char *sc = strchr(temp, ';');// Find the position of the ';' character in the line, which separates the comp and jump parts of the C-instruction. Similar to eq, the strchr function is used to locate the first occurrence of ';' in the temp string, and it returns a pointer to that position. If ';' is not found, sc will be NULL.

    if (eq) {
        *eq = '\0';
        strcpy(dest, temp); // If '=' is found, the dest part is the substring before '=', and the comp part is the substring after '='. The function sets the character at eq to '\0' to terminate the dest string, and then copies the dest and comp parts into their respective variables.
        strcpy(comp, eq + 1);
    } else {
        strcpy(dest, "null");
        strcpy(comp, temp);
    }

    if (sc) {
        *sc = '\0';
        strcpy(comp, eq ? eq + 1 : temp);// If ';' is found, the jump part is the substring after ';'. The function sets the character at sc to '\0' to terminate the comp string, and then copies the jump part into its variable. If '=' was not found, the comp part is the entire line (temp), otherwise it is the substring after '='.
        strcpy(jump, sc + 1);
    } else {
        strcpy(jump, "null");
    }
}