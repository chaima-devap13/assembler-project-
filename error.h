#ifndef ERROR_H
#define ERROR_H
extern int errorCount;
void errorInvalidA(char *line, int lineNumber);
void errorInvalidComp(char *comp, int lineNumber, char *line);
void errorInvalidDest(char *dest, int lineNumber, char *line);
void errorInvalidJump(char *jump, int lineNumber, char *line);
void errorDuplicateLabel(char *label, int lineNumber);
void errorInvalidSyntax(char *line, int lineNumber);
#endif