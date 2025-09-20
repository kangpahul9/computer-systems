load ArrSort.asm,
// Sample Test file for ArrSort.asm
// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load ArrSort.asm,
output-file ArrSort05.out,
compare-to ArrSort05.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[100]%D2.6.2 RAM[101]%D2.6.2 RAM[102]%D2.6.2 RAM[103]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  100, // Set R1
set RAM[2]  5,  // Set R2
set RAM[100] 9,  // Set Arr[0]
set RAM[101] -4,  // Set Arr[1]
set RAM[102] 3,  // Set Arr[2]
set RAM[103] -1;  // Set Arr[3]
repeat 600 {
  ticktock;    // Run for 600 clock cycles
}
set RAM[1] 100,  // Restore arguments in case program used them
set RAM[2] 5,
output;        // Output to file


