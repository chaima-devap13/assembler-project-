#ifndef PARSER_H
#define PARSER_H

#define A_COMMAND 0
#define C_COMMAND 1
#define L_COMMAND 2

int commandType(char *line);
void getSymbol(char *line, char *symbol);
void parseC(char *line, char *dest, char *comp, char *jump);

#endif