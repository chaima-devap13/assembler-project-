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