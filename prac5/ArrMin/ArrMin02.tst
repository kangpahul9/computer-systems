// Test case 2: Minimum is in the middle
load ArrMin.asm,
output-file ArrMin02.out,
compare-to ArrMin02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[40]%D2.6.2 RAM[41]%D2.6.2 RAM[42]%D2.6.2 RAM[43]%D2.6.2;

set PC 0,
set RAM[0]  0,
set RAM[1]  40,
set RAM[2]  4,
set RAM[40] 50,
set RAM[41] 25,
set RAM[42] -10,
set RAM[43] 5;

repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 40,  // Restore arguments in case program used them
set RAM[2] 4,
output;  
