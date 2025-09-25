// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// R0 = min(RAM[R1]..RAM[R1+R2-1])
@2
D=M
@EMPTY
D;JEQ

@2
D=M
D=D-1
@ONE
D;JEQ

@1
D=M
A=D
D=M
@0
M=D

@3
M=1

(LOOP)
    @3
    D=M
    @2
    D=D-M
    @END
    D;JGE

    @1
    D=M
    @3
    D=D+M
    @4
    M=D
    @4
    A=M
    D=M

    @0
    D=D-M
    @SKIP
    D;JGE

    @4
    A=M
    D=M
    @0
    M=D

(SKIP)
    @3
    M=M+1
    @LOOP
    0;JMP

(EMPTY)
    @0
    M=0
    @END
    0;JMP

(ONE)
    @1
    D=M
    A=D
    D=M
    @0
    M=D
    @END
    0;JMP

(END)
    @END
    0;JMP