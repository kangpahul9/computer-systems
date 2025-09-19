// Test case 3: Array of length 1
load ArrMin.asm,
output-file ArrMin03.out,
compare-to ArrMin03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[70]%D2.6.2;

set PC 0,
set RAM[0]  0,
set RAM[1]  70,
set RAM[2]  1,
set RAM[70] -123;

repeat 150 {
  ticktock;    // Run for 150 clock cycles
}
set RAM[1] 70,  // Restore arguments in case program used them
set RAM[2] 1,
output;        // Output to file

