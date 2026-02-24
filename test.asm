// Store first number
@5
D=A
@num1
M=D

// Store second number
@3
D=A
@num2
M=D

// result = num1 + num2
@num1
D=M
@num2
D=D+M
@result
M=D

(END)
@END
0;JMP