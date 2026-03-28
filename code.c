#include <stdio.h>
#include <string.h>
#include "code.h"
#include"error.h"
   // into binary : from assambly via binary with shift and bitwise operations
void intToBinary(int value, char *output) {
    for (int i = 0; i < 16; i++) {
        output[i] = ((value >> (15 - i)) & 1) + '0';
    }
    output[16] = '\0';
}
/* ------------------ ENCODE A ------------------ */
  // ecodeA takes an integer value and converts it to a 16-bit binary string, which is stored in the output parameter. The function uses bitwise operations to extract each bit from the integer and constructs the binary string accordingly 
void encodeA(int value, char *output) {
    intToBinary(value, output);
}

/* ------------------ DEST TABLE ------------------ */
  // destTable takes a destination mnemonic (dest) and returns the corresponding 3-bit binary code as a string. It uses a series of if statements to match the input mnemonic with its binary representation. If the input does not match any valid mnemonic, it calls an error handling function and returns NULL
char* destTable(char *dest,int lineNumber,char *line) {
    if (strcmp(dest, "null") == 0) return "000"; 
    if (strcmp(dest, "M") == 0)   return "001";
    if (strcmp(dest, "D") == 0)   return "010";
    if (strcmp(dest, "MD") == 0)  return "011";
    if (strcmp(dest, "A") == 0)   return "100";
    if (strcmp(dest, "AM") == 0)  return "101";
    if (strcmp(dest, "AD") == 0)  return "110";
    if (strcmp(dest, "AMD") == 0) return "111";
    errorInvalidDest(dest, lineNumber, line);
    return NULL;
}

/* ------------------ JUMP TABLE ------------------ */

char* jumpTable(char *jump,int lineNumber,char *line) {
    if(strcmp(jump,"null")==0) return "000";
    if (strcmp(jump, "JGT") == 0) return "001";
    if (strcmp(jump, "JEQ") == 0) return "010";
    if (strcmp(jump, "JGE") == 0) return "011";
    if (strcmp(jump, "JLT") == 0) return "100";
    if (strcmp(jump, "JNE") == 0) return "101";
    if (strcmp(jump, "JLE") == 0) return "110";
    if (strcmp(jump, "JMP") == 0) return "111";
    errorInvalidJump(jump, lineNumber, line);
    return NULL;
}

/* ------------------  ------------------ */

char* compTable(char *comp, int lineNumber, char *line) {

    if (strcmp(comp, "0") == 0)   return "0101010";
    if (strcmp(comp, "1") == 0)   return "0111111";
    if (strcmp(comp, "-1") == 0)  return "0111010";
    if (strcmp(comp, "D") == 0)   return "0001100";
    if (strcmp(comp, "A") == 0)   return "0110000";
    if (strcmp(comp, "!D") == 0)  return "0001101";
    if (strcmp(comp, "!A") == 0)  return "0110001";
    if (strcmp(comp, "-D") == 0)  return "0001111";
    if (strcmp(comp, "-A") == 0)  return "0110011";
    if (strcmp(comp, "D+1") == 0) return "0011111";
    if (strcmp(comp, "A+1") == 0) return "0110111";
    if (strcmp(comp, "D-1") == 0) return "0001110";
    if (strcmp(comp, "A-1") == 0) return "0110010";
    if (strcmp(comp, "D+A") == 0) return "0000010";
    if (strcmp(comp, "D-A") == 0) return "0010011";
    if (strcmp(comp, "A-D") == 0) return "0000111";
    if (strcmp(comp, "D&A") == 0) return "0000000";
    if (strcmp(comp, "D|A") == 0) return "0010101";

    // when a = 1 (M operations)

    if (strcmp(comp, "M") == 0)   return "1110000";
    if (strcmp(comp, "!M") == 0)  return "1110001";
    if (strcmp(comp, "-M") == 0)  return "1110011";
    if (strcmp(comp, "M+1") == 0) return "1110111";
    if (strcmp(comp, "M-1") == 0) return "1110010";
    if (strcmp(comp, "D+M") == 0) return "1000010";
    if (strcmp(comp, "D-M") == 0) return "1010011";
    if (strcmp(comp, "M-D") == 0) return "1000111";
    if (strcmp(comp, "D&M") == 0) return "1000000";
    if (strcmp(comp, "D|M") == 0) return "1010101";

    
    errorInvalidComp(comp, lineNumber, line);
return NULL;
}

/* ------------------ ENCODE C ------------------ */

void encodeC(char *dest, char *comp, char *jump, char *output, int lineNumber, char *line) {

    char *compBits = compTable(comp, lineNumber, line);
    char *destBits = destTable(dest, lineNumber, line);
    char *jumpBits = jumpTable(jump, lineNumber, line);

    if (compBits == NULL || destBits == NULL || jumpBits == NULL) {
        output[0] = '\0';   
        return;
    }

    sprintf(output, "111%s%s%s", compBits, destBits, jumpBits);
}