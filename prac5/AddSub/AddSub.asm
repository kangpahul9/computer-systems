// Calculates R1 + R2 - R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

// Put your code here.

@0
M=0
@1
D=M
@0
M=D
@2
D=M
@0
M=M+D
@3
D=M
@0
M=M-D
(END)
    @END
    0;JMP