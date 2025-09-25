// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// R0 = min(RAM[R1]..RAM[R1+R2-1])
@2
D=M
@EMPTY
D;JEQ        

@1
D=M
@2
D=D+M
D=D-1
@2
M=D           

@1
A=M
D=M
@0
M=D

@1
D=M
D=D+1
@3
M=D

(LOOP)
    @3
    D=M
    @2
    D=D-M
    @END
    D;JGT

    @3
    A=M
    D=M
    @ELEM_POS
    D;JGE        
    @ELEM_NEG
    0;JMP        

(UPDATE)
    @3
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

(END)
    @END
    0;JMP

(REF_NEG)
    
(REF_POS)
    @3
    A=M
    D=M
    @0
    D=D-M       
    @SKIP
    D;JGE       
    @UPDATE
    0;JMP

(ELEM_NEG)
    @0
    D=M
    @REF_NEG
    D;JLT        
    @UPDATE      
    0;JMP

(ELEM_POS)
    @0
    D=M
    @REF_POS
    D;JGE       
    @SKIP       
    0;JMP