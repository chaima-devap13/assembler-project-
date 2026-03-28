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
            addSymbol(symbol, address);
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
                    addSymbol(symbol, nextVarAddress++);
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
   // Prompt the user to enter the name of the .asm file to be assembled. The filename is read from standard input and stored in the variable 'filename'. This allows the user to specify which assembly file they want to process.
    char filename[100];

    printf("Enter .asm file name: ");
    scanf("%s", filename);

    FILE *input = fopen(filename, "r"); // r=read mode, open the specified file for reading. If the file cannot be opened (e.g., if it does not exist), the program will print an error message and exit with a non-zero status code. This ensures that the program does not proceed with an invalid input file, which could lead to further errors down the line.

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

    

    printf("\nInput file opened successfully!\n");
    printf("Output file will be: %s\n", outputName);

    /* ---------------------- */

    initSymbolTable(); // Initialize the symbol table before starting the assembly process. This function sets up the necessary data structures to store symbols and their corresponding addresses, which will be used during the first pass to populate the symbol table with labels and during the second pass to resolve symbols in A-instructions.

    pass1(input); // Perform the first pass on the input file to populate the symbol table with labels and their corresponding addresses. This pass reads through the assembly code, identifies label definitions (L_COMMAND), and adds them to the symbol table. It also keeps track of the current address for A_COMMAND and C_COMMAND instructions, which is essential for resolving symbols in the second pass.

    
    rewind(input); // Reset the file pointer to the beginning of the input file after completing the first pass. This allows the second pass to read through the file again from the start, this time translating A_COMMAND and C_COMMAND instructions into their binary representations using the symbol table populated in the first pass.

   

    pass2(input, NULL);
if (errorCount == 0) {

    FILE *output = fopen(outputName, "w");

    if (output == NULL) {
        printf("Error creating output file\n");
        fclose(input);
        return 1;
    }

    rewind(input);// Reset the file pointer to the beginning of the input file again before starting the second pass, ensuring that we read through the file from the start for encoding.

    pass2(input, output);

    fclose(output);// Close the output file after writing the encoded binary instructions. This is important to ensure that all data is properly flushed to the file and that system resources are released.

    printSymbolTable();

    printf("\nTranslation finished successfully.\n");

} else {

    printf("\nSymbol table not generated due to errors.\n");
    printf("\n%d errors found.\n", errorCount);
}
    



    return 0;
}