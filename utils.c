#include <string.h>
#include <ctype.h>
#include <stdlib.h>
// Utility functions for the Hack assembler, including line cleaning, symbol validation, and syntax checking. These functions are used throughout the assembly process to ensure that the input assembly code is properly formatted and to assist in error handling. The cleanLine function removes comments and whitespace from a line of code, while the isValidSymbol and isValidAValue functions check for valid symbols and A-instruction values. The isValidCFormat function checks for correct syntax in C-instructions.
// The cleanLine function takes a line of assembly code and removes any comments (denoted by "//") and whitespace characters. It modifies the input line in place, resulting in a cleaned version of the line that can be further processed for parsing and encoding.
void cleanLine(char *line) {

    char *comment = strstr(line, "//");
    if (comment) *comment = '\0'; // Truncate the line at the start of the comment, effectively removing it

    int i = 0, j = 0;
    while (line[i]) {
        if (!isspace(line[i])) { // If the current character is not a whitespace character, copy it to the position indicated by j and increment j. This effectively removes all whitespace characters from the line.
            line[j++] = line[i];
        }
        i++;
    }
    line[j] = '\0';
}
 //isValidSymbol checks if a given symbol is valid according to the Hack assembly language specifications. A valid symbol must start with a letter, underscore, dot, dollar sign, or colon, and can be followed by letters, digits, underscores, dots, dollar signs, or colons. The function returns 1 if the symbol is valid and 0 otherwise.
int isValidSymbol(char *symbol) {
    if (symbol == NULL || symbol[0] == '\0') {
        return 0;
    }
  // The first character of the symbol must be a letter, underscore, dot, dollar sign, or colon. If the first character does not meet this requirement, the function returns 0, indicating that the symbol is invalid.
    if (!(isalpha(symbol[0]) || symbol[0] == '_' || symbol[0] == '.' || symbol[0] == '$' || symbol[0] == ':')) {
        return 0;
    }
// The subsequent characters of the symbol can be letters, digits, underscores, dots, dollar signs, or colons. The function iterates through the characters of the symbol starting from the second character (index 1) and checks if each character meets these criteria. If any character does not meet the requirements, the function returns 0, indicating that the symbol is invalid.
    for (int i = 1; i < strlen(symbol); i++) {
        if (!(isalnum(symbol[i]) || symbol[i] == '_' || symbol[i] == '.' || symbol[i] == '$' || symbol[i] == ':')) {
            return 0;
        }
    }

    return 1;
}
 // isValidAValue checks if a given symbol is a valid A-instruction value. A valid A-instruction value can either be a non-negative integer (0 to 32767) or a valid symbol. The function first checks if the symbol is a valid number by verifying that all characters are digits and that the resulting integer falls within the allowed range. If the symbol is not a valid number, it checks if it is a valid symbol using the isValidSymbol function. The function returns 1 if the symbol is a valid A-instruction value and 0 otherwise.
int isValidAValue(char *symbol) {

    if (symbol == NULL || symbol[0] == '\0')
        return 0;

    if (isdigit(symbol[0])) {

        for (int i = 0; i < strlen(symbol); i++) {
            if (!isdigit(symbol[i]))
                return 0;
        }

        int value = atoi(symbol); // Convert the symbol to an integer using atoi, which is a standard library function that converts a string to an integer. The function then checks if the resulting integer value is within the valid range for A-instruction values (0 to 32767). If the value is outside this range, the function returns 0, indicating that it is not a valid A-instruction value.

        if (value < 0 || value > 32767)
            return 0;

        return 1;
    }

    return isValidSymbol(symbol);
}
// isValidCFormat checks if a given line of code follows the correct syntax for a C-instruction in the Hack assembly language. It verifies that there is at most one '=' character (which separates dest and comp) and at most one ';' character (which separates comp and jump). It also checks that if '=' is present, it is not the first character, and if ';' is present, it is not the last character. Additionally, if both '=' and ';' are present, it ensures that '=' comes before ';'. The function returns 1 if the line has a valid C-instruction format and 0 otherwise.
int isValidCFormat(char *line) {

    int eqCount = 0;
    int scCount = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '=') eqCount++;
        if (line[i] == ';') scCount++;
    }

    if (eqCount > 1 || scCount > 1)
        return 0;
 //ndfhp fkdlpd
    if (eqCount == 1) {
        if (line[0] == '=')
            return 0;
    }

    if (scCount == 1) {
        if (line[strlen(line) - 1] == ';')
            return 0;
    }

    if (eqCount == 1 && scCount == 1) {
        char *eq = strchr(line, '=');
        char *sc = strchr(line, ';');

        if (eq > sc)
            return 0;
    }
 //ndfhp fkdlpd
    return 1;
}