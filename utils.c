#include <string.h>
#include <ctype.h>

void cleanLine(char *line) {

    char *comment = strstr(line, "//");
    if (comment) *comment = '\0';

    int i = 0, j = 0;
    while (line[i]) {
        if (!isspace(line[i])) {
            line[j++] = line[i];
        }
        i++;
    }
    line[j] = '\0';
}
int isValidSymbol(char *symbol) {
    if (symbol == NULL || symbol[0] == '\0') {
        return 0;
    }

    if (!(isalpha(symbol[0]) || symbol[0] == '_' || symbol[0] == '.' || symbol[0] == '$' || symbol[0] == ':')) {
        return 0;
    }

    for (int i = 1; i < strlen(symbol); i++) {
        if (!(isalnum(symbol[i]) || symbol[i] == '_' || symbol[i] == '.' || symbol[i] == '$' || symbol[i] == ':')) {
            return 0;
        }
    }

    return 1;
}