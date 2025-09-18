// Calculates the absolute value of R1 and stores the result in R0.
// (R0, R1 refer to RAM[0], and RAM[1], respectively.)

// Put your code here.

@0
M=0
@1
D=M
@OUTPUT_ONE
    D;JGE
@OUTPUT_TWO
    0;JMP
(OUTPUT_TWO)
    @1
    D=M
    D=-D
    @0
    M=D
(OUTPUT_ONE)
    @0
    M=D
(END)
    @END
    0;JMP
