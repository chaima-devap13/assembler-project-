#ifndef ERROR_H
#define ERROR_H

void errorInvalidA(char *line, int lineNumber);
void errorInvalidComp(char *comp, int lineNumber);
void errorInvalidDest(char *dest, int lineNumber);
void errorInvalidJump(char *jump, int lineNumber);
void errorDuplicateLabel(char *label, int lineNumber);

#endif