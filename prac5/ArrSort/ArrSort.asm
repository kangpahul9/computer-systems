// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Input:
// RAM[1] = base address of arr[0]
// RAM[2] = length
// Output: array sorted in place
// RAM[0] = -1 when finished
  @1           // the address of arr[0]
    D=M-1        // subtract 1 because the array starts from arr[0]
    @2           // the length
    M=M+D        // now R2 is the address of the last element

(LOOP_OUTER)
(CHK_TERM)
    @1
    D=M
    @2
    D=D-M
    @DONE
    D;JGT
    @1
    D=M
    @3          // inner loop index
    M=D+1 

(LOOP_INNER)
(CHK_INNER)
    @3
    D=M
    @2
    D=D-M
    @INNER_END
    D;JGT
    @3
    A=M
    D=M
    @ELEM_POS
    D;JGE
    @ELEM_NEG
    0;JMP

(SWAP_VAL)
    @1
    A=M
    D=M
    @13
    M=D
    @3
    A=M
    D=M
    @1
    A=M
    M=D
    @13
    D=M
    @3
    A=M
    M=D
(SKIP_SWAP)
    @3
    M=M+1
    @LOOP_INNER
    0;JMP

(INNER_END)
    @1
    M=M+1
    @LOOP_OUTER
    0;JMP

(DONE)
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
    @SKIP_SWAP
    D;JGE
    @SWAP_VAL
    0;JMP

(ELEM_NEG)
    @1
    A=M
    D=M
    @REF_NEG
    D;JLT
    @SWAP_VAL
    0;JMP

(ELEM_POS)
    @1
    A=M
    D=M
    @REF_POS
    D;JGE
    @SKIP_SWAP
    0;JMP