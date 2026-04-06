#ifndef PARSER_H
#define PARSER_H
 //ndfhp fkdlpd
#define A_COMMAND 0 // A_COMMAND represents an A-instruction in the Hack assembly language, which is used to set the value of the A register or to reference a symbol. The commandType function checks if a line starts with '@' to identify it as an A_COMMAND.
#define C_COMMAND 1 // C_COMMAND represents a C-instruction in the Hack assembly language, which is used for computations and control flow. If a line does not start with '@' or '(', it is classified as a C_COMMAND by the commandType function.
#define L_COMMAND 2 // L_COMMAND represents a label declaration in the Hack assembly language, which defines a label that can be used as a symbol in A-instructions. The commandType function checks if a line starts with '(' to identify it as an L_COMMAND.

int commandType(char *line);
void getSymbol(char *line, char *symbol);
void parseC(char *line, char *dest, char *comp, char *jump);

#endif