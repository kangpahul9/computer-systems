// Array = [1, 2, 3, 4, 5]
load ArrMin.asm,
output-file ArrMin01.out,
compare-to ArrMin01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[30]%D2.6.2 RAM[31]%D2.6.2 RAM[32]%D2.6.2 RAM[33]%D2.6.2;

set RAM[1] 10;   // base address = 10
set RAM[2] 5;    // length = 5

set RAM[10] 1;
set RAM[11] 2;
set RAM[12] 3;
set RAM[13] 4;
set RAM[14] 5;

repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 10,  // Restore arguments in case program used them
set RAM[2] 5,
output;        // Output to file
