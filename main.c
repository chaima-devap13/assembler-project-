#include <stdio.h>
#include "parser.h"
#include "symboltable.h"
#include "code.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "error.h"

void pass1(FILE *input); // Pass 1 reads the input assembly file line by line, cleans each line, and processes label definitions (L_COMMAND). It maintains a symbol table to keep track of labels and their corresponding addresses. For each L_COMMAND, it extracts the label name and adds it to the symbol table with the current address. For A_COMMAND and C_COMMAND, it simply increments the address counter. This pass is essential for resolving label references in the second pass.
void pass2(FILE *input, FILE *output);// Pass 2 reads the input assembly file again, this time translating A_COMMAND and C_COMMAND into their binary representations. For A_COMMAND, it checks if the symbol is a valid number or a variable, and encodes it accordingly. For C_COMMAND, it parses the dest, comp, and jump parts, retrieves their binary codes from the corresponding tables, and constructs the final binary instruction. The resulting binary code is written to the output file. This pass relies on the symbol table populated in Pass 1 to resolve symbols to addresses.


void pass1(FILE *input) {
    char line[256];
    int address = 0;
    int lineNumber = 0; // Line number counter to track the current line being processed, which is useful for error reporting and debugging. It is incremented for each line read from the input file.
    while (fgets(line, sizeof(line), input)) { 
        lineNumber++;// Read each line from the input file and increment the line number counter. This allows us to keep track of which line we are currently processing, which is important for error handling and reporting.
        cleanLine(line); 
        if (strlen(line) == 0) continue;

        if (commandType(line) == L_COMMAND) {
            char symbol[50];
            getSymbol(line, symbol);
           if (containsSymbol(symbol)) {
               errorDuplicateLabel(symbol, lineNumber);
            }
            addSymbol(symbol, address,LABEL);
        } else {
            address++;
        }
    }
   
}
    



void pass2(FILE *input, FILE *output) {
    char line[256];
    int lineNumber = 0;// Line number counter to track the current line being processed, which is useful for error reporting and debugging. It is incremented for each line read from the input file.
    int nextVarAddress = 16;// Next available address for variable symbols, starting from 16 as per the Hack assembly specification. This variable is used to assign addresses to new symbols encountered in A_COMMANDs that are not already in the symbol table.

    while (fgets(line, sizeof(line), input)) {
        lineNumber++;
        cleanLine(line);
        if (strlen(line) == 0) continue;

        int type = commandType(line);

        if (type == A_COMMAND) {
            char symbol[50];
            getSymbol(line, symbol);

        if (!isValidAValue(symbol)) {
        errorInvalidA(symbol, lineNumber);
    }

            int value;
            if (isdigit(symbol[0])) {
                value = atoi(symbol);
            } else {
                if (!containsSymbol(symbol)) {
                    addSymbol(symbol, nextVarAddress++,VARIABLE);
                }
                value = getAddress(symbol);
            }

            char binary[17];
            binary[0] = '\0';// Initialize the binary string to an empty string before encoding
            encodeA(value, binary);
            if (output != NULL) {
    fprintf(output, "%s\n", binary);// Write the encoded binary string to the output file, followed by a newline character. This is done only if the output file pointer is not NULL, ensuring that we do not attempt to write to an invalid file.
}
        }

        else if (type == C_COMMAND) {
            
            if (!isValidCFormat(line)) {
    errorInvalidSyntax(line, lineNumber);
       continue;
       }
       char dest[10], comp[20], jump[10];
            parseC(line, dest, comp, jump);// Parse the C-instruction line to extract the dest, comp, and jump components. The parseC function fills the dest, comp, and jump variables based on the syntax of the C-instruction. This allows us to later encode these components into their binary representations.

            char binary[17];
            binary[0] = '\0';// Initialize the binary string to an empty string before encoding
encodeC(dest, comp, jump, binary, lineNumber, line);

if (binary[0] != '\0') {
    if (output != NULL) {
        fprintf(output, "%s\n", binary);
    }
}
        }
    }
}

int main() {

    char filename[100];
    char choice;

    do {
        printf("\nEnter .asm file name: ");
        scanf("%s", filename);

        FILE *input = fopen(filename, "r");

        if (input == NULL) {
            printf("Error: cannot open file %s\n", filename);
            continue; 
        }
     
        char outputName[100];
        strcpy(outputName, filename);

        char *dot = strrchr(outputName, '.');
        if (dot != NULL) {
            strcpy(dot, ".obj");
        } else {
            strcat(outputName, ".obj");
        }

        printf("\nInput file opened successfully!\n");
        printf("Output file will be: %s\n", outputName);

        
        initSymbolTable();
      errorCount = 0;
    
        pass1(input);

        rewind(input);

        pass2(input, NULL);

        if (errorCount == 0) {

            FILE *output = fopen(outputName, "w");

            if (output == NULL) {
                printf("Error creating output file\n");
                fclose(input);
                continue;
            }

            rewind(input);
            pass2(input, output);

            fclose(output);

            printSymbolTable();
            printf("\nTranslation finished successfully.\n");

        } else {
            printf("\nSymbol table not generated due to errors.\n");
            printf("%d errors found.\n", errorCount);
        }

        fclose(input);

        
        printf("\nDo you want to process another file? (y/n): ");
        scanf(" %c", &choice); // space مهم

    } while (choice == 'y' || choice == 'Y');

    printf("\nProgram terminated.\n");
    return 0;
}