// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Input:
// RAM[1] = base address of arr[0]
// RAM[2] = length
// Output: array sorted in place
// RAM[0] = -1 when finished

@2
D=M
@DONE
D;JEQ
@2
D=M
D=D-1
@DONE
D;JEQ

@3
M=0

(OUTER)
    @3
    D=M
    @2
    D=D-M
    @DONE
    D;JGE

    @3
    D=M
    @6
    M=D

    @3
    D=M
    D=D+1
    @5
    M=D

(INNER)
    @5
    D=M
    @2
    D=D-M
    @AFTER_INNER
    D;JGE

    @1
    D=M
    @5
    D=D+M
    A=D
    D=M
    @4
    M=D

    @1
    D=M
    @6
    D=D+M
    A=D
    D=M
    @REF_POS
    D;JGE
    @REF_NEG
    0;JMP

(REF_POS)
    @4
    D=M
    @6
    D=M
    @1
    D=D+M
    A=D
    D=M
    @4
    D=M-D
    @SKIP
    D;JGE
    @5
    D=M
    @6
    M=D
    @SKIP
    0;JMP

(REF_NEG)
    @4
    D=M
    @6
    D=M
    @1
    D=D+M
    A=D
    D=M
    @4
    D=M
    @SKIP
    D;JGE
    @5
    D=M
    @6
    M=D

(SKIP)
    @5
    M=M+1
    @INNER
    0;JMP

(AFTER_INNER)
    @3
    D=M
    @6
    D=D-M
    @NO_SWAP
    D;JEQ

    @1
    D=M
    @3
    D=D+M
    @8
    M=D

    @1
    D=M
    @6
    D=D+M
    @9
    M=D

    @8
    A=M
    D=M
    @7
    M=D

    @9
    A=M
    D=M
    @8
    A=M
    M=D

    @7
    D=M
    @9
    A=M
    M=D

(NO_SWAP)
    @3
    M=M+1
    @OUTER
    0;JMP

(DONE)
    @0
    M=-1
(END)
    @END
    0;JMP