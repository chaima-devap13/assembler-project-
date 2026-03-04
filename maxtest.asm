// Put first number in R0
@7
D=A
@R0
M=D

// Put second number in R1
@3
D=A
@R1
M=D

// Compare R0 and R1
@R0
D=M
@R1
D=D-M
@FIRST
D;JGT

// If not greater, result = R1
@R1
D=M
@RESULT
M=D
@END
0;JMP

(FIRST)
// result = R0
@R0
D=M
@RESULT
M=D

(END)
@END
0;JMP