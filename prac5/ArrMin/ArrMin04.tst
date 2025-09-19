// Test case 4: All elements are negative
load ArrMin.asm,
output-file ArrMin04.out,
compare-to ArrMin04.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[80]%D2.6.2 RAM[81]%D2.6.2 RAM[82]%D2.6.2 RAM[83]%D2.6.2;

set PC 0,
set RAM[0]  0,
set RAM[1]  80,
set RAM[2]  4,
set RAM[80] -1,
set RAM[81] -5,
set RAM[82] -3,
set RAM[83] -7;

repeat 400 {
  ticktock;    // Run for 400 clock cycles
}
set RAM[1] 80,  // Restore arguments in case program used them
set RAM[2] 4,
output;        // Output to file

