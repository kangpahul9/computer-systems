// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Input:
// RAM[1] = base address of arr[0]
// RAM[2] = length
// Output: array sorted in place
// RAM[0] = -1 when finished

@1
D=M
@2
D=D+M
D=D-1
@2
M=D       

(OUTER_LOOP)
(CHECK_TERMINATE)
    @1
    D=M
    @2
    D=D-M
    @FINISH
    D;JGT       

    @1
    D=M
    @3
    M=D+1       

(INNER_LOOP)
(CHECK_INNER_END)
    @3
    D=M
    @2
    D=D-M
    @INNER_FINISH
    D;JGT       

    @3
    A=M
    D=M
    @ELEM_POS
    D;JGE
    @ELEM_NEG
    0;JMP

(SWAP)
    @1
    A=M
    D=M
    @5
    M=D       

    @3
    A=M
    D=M
    @1
    A=M
    M=D       

    @5
    D=M
    @3
    A=M
    M=D       

(SKIP)
    @3
    M=M+1
    @INNER_LOOP
    0;JMP

(INNER_FINISH)
    @1
    M=M+1      
    @OUTER_LOOP
    0;JMP

(FINISH)
    @0
    M=-1
(END)
    @END
    0;JMP

(REF_NEG)
    
(REF_POS)
    @3
    A=M
    D=M
    @1
    A=M
    D=D-M      
    @SKIP
    D;JGE
    @SWAP
    0;JMP

(ELEM_NEG)
    @1
    A=M
    D=M
    @REF_NEG
    D;JLT
    @SWAP
    0;JMP

(ELEM_POS)
    @1
    A=M
    D=M
    @REF_POS
    D;JGE
    @SKIP
    0;JMP