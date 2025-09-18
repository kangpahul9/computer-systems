// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@0
M=0
@1
D=M
@3
M=D
@2
D=M
@4
M=D
@5
M=0

@3
D=M
@ONE_NOTNEG
D;JGT
    @3
    M=-M
    @5
    M=M+1

(ONE_NOTNEG)

@4
D=M
@TWO_NOTNEG
D;JGT
    @4
    M=-M
    @5
    M=M+1

(TWO_NOTNEG)

(LOOP)
    @3
    D=M
    @LOOP_OVER
    D;JEQ
    @4
    D=M
    @0
    M=D+M
    @3
    M=M-1
    @LOOP
    0;JMP
(LOOP_OVER)
    @5
    D=M;
    @CHANGE
    D;JEQ
    @0
    M=-M
(CHANGE)
(END)
    @END
    0;JMP
