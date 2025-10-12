// Sample Test file for ArrMax.asm
// Finds max among {50, 40, 30, 20, 10}

load ArrMax.vm,
output-file ArrMax02.out,
// compare-to ArrMax02.cmp,
output-list sp%D1.6.1 local%D1.6.1 argument%D1.8.1 this%D1.6.1 that%D1.6.1
            RAM[16]%D1.6.1 RAM[17]%D1.6.1 RAM[18]%D1.6.1
            local[0]%D1.8.1 local[1]%D1.8.1 local[2]%D1.8.1
            argument[0]%D1.11.1 argument[1]%D1.11.1 argument[2]%D1.11.1;

set sp 256,
set local 300,
set argument 400,
set this 3000,
set that 3010,

set RAM[16] 0,
set RAM[17] 2100,
set RAM[18] 5,

set argument[0] 2100,
set argument[1] 5,

set RAM[2100] 50,
set RAM[2101] 40,
set RAM[2102] 30,
set RAM[2103] 20,
set RAM[2104] 10;

repeat 200 {
  vmstep;
}
output;
