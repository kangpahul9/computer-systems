// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Input:
// RAM[1] = base address of arr[0]
// RAM[2] = length
// Output: array sorted in place
// RAM[0] = -1 when finished

// --- Convert length to last address ---
@1
D=M
@2
D=D+M        
D=D-1        
@2
M=D          

(OUTER)
    @1
    D=M
    @2
    D=D-M
    @DONE
    D;JGT        

    @1
    D=M
    D=D+1
    @3
    M=D

(INNER)
    @3
    D=M
    @2
    D=D-M
    @AFTER_INNER
    D;JGT        

    @3
    A=M
    D=M
    @4
    M=D        

    @1
    A=M
    D=M        

    @4
    D=M-D
    @SKIP
    D;JGE      
    @SWAP
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

    // *RAM[3] = RAM[5]
    @5
    D=M
    @3
    A=M
    M=D

(SKIP)
    // RAM[3]++
    @3
    M=M+1
    @INNER
    0;JMP

(AFTER_INNER)
    // RAM[1]++
    @1
    M=M+1
    @OUTER
    0;JMP

(DONE)
    @0
    M=-1
(END)
    @END
    0;JMP