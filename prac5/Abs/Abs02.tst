// Sample Test file for Abs.asm
// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load Abs.asm,
output-file Abs02.out,
compare-to Abs02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 21000;  // Set R1
repeat 500 {
  ticktock;    // Run for 500 clock cycles
}
set RAM[1] 21000,  // Restore arguments in case program used them
output;        // Output to file

