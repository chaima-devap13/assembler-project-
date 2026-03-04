#include <stdio.h>
#include "parser.h"
#include "symboltable.h"
#include "code.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void pass1(FILE *input);
void pass2(FILE *input, FILE *output);


void pass1(FILE *input) {
    char line[256];
    int address = 0;

    while (fgets(line, sizeof(line), input)) {
        cleanLine(line);
        if (strlen(line) == 0) continue;

        if (commandType(line) == L_COMMAND) {
            char symbol[50];
            getSymbol(line, symbol);
            addSymbol(symbol, address);
        } else {
            address++;
        }
    }
}

void pass2(FILE *input, FILE *output) {
    char line[256];
    int nextVarAddress = 16;

    while (fgets(line, sizeof(line), input)) {
        cleanLine(line);
        if (strlen(line) == 0) continue;

        int type = commandType(line);

        if (type == A_COMMAND) {
            char symbol[50];
            getSymbol(line, symbol);

            int value;
            if (isdigit(symbol[0])) {
                value = atoi(symbol);
            } else {
                if (!containsSymbol(symbol)) {
                    addSymbol(symbol, nextVarAddress++);
                }
                value = getAddress(symbol);
            }

            char binary[17];
            encodeA(value, binary);
            fprintf(output, "%s\n", binary);
        }

        else if (type == C_COMMAND) {
            char dest[10], comp[20], jump[10];
            parseC(line, dest, comp, jump);

            char binary[17];
            encodeC(dest, comp, jump, binary);

            fprintf(output, "%s\n", binary);
        }
    }
}

int main() {

    char filename[100];

    printf("Enter .asm file name: ");
    scanf("%s", filename);

    FILE *input = fopen(filename, "r");

    if (input == NULL) {
        printf("Error: cannot open file %s\n", filename);
        return 1;
    }

    /* --------------------- */

    char outputName[100];
    strcpy(outputName, filename);

    char *dot = strrchr(outputName, '.');

    if (dot != NULL) {
        strcpy(dot, ".obj");
    } else {
        strcat(outputName, ".obj");
    }

    FILE *output = fopen(outputName, "w");

    if (output == NULL) {
        printf("Error creating output file\n");
        fclose(input);
        return 1;
    }

    printf("\nInput file opened successfully!\n");
    printf("Output file will be: %s\n", outputName);

    /* ---------------------- */

    initSymbolTable();

    pass1(input);

    
    rewind(input);

   

    pass2(input, output);

    

    printSymbolTable();

    fclose(input);
    fclose(output);

    printf("Translation finished successfully.\n");

    return 0;
}