// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@2
D=M
@DONE
D;JEQ
@2
D=M
D=D-1
@DONE
D;JEQ

// i = 0
@3
M=0

(OUTER)
    @3
    D=M
    @2
    D=D-M
    @DONE
    D;JGE

    // minIndex = i
    @3
    D=M
    @6
    M=D

    // j = i+1
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

    // load arr[j] → R4
    @1
    D=M
    @5
    D=D+M
    A=D
    D=M
    @4
    M=D

    // load arr[minIndex] → D
    @1
    D=M
    @6
    D=D+M
    A=D
    D=M

    // compare arr[j] vs arr[minIndex]
    @4
    D=M-D
    @SKIP
    D;JGE
    @5
    D=M
    @6
    M=D
(SKIP)

    // j++
    @5
    M=M+1
    @INNER
    0;JMP

(AFTER_INNER)
    // if minIndex == i → no swap
    @3
    D=M
    @6
    D=D-M
    @NO_SWAP
    D;JEQ

    // addrI = base+i → R8
    @1
    D=M
    @3
    D=D+M
    @8
    M=D

    // addrMin = base+minIndex → R9
    @1
    D=M
    @6
    D=D+M
    @9
    M=D

    // temp = arr[i] → R7
    @8
    A=M
    D=M
    @7
    M=D

    // arr[i] = arr[minIndex]
    @9
    A=M
    D=M
    @8
    A=M
    M=D

    // arr[minIndex] = temp
    @7
    D=M
    @9
    A=M
    M=D

(NO_SWAP)
    // i++
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