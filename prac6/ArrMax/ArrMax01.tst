// Sample Test file for ArrMax.asm
// Finds max among {5, 9, 3, 7, 2}

load ArrMax.vm,
output-file ArrMax01.out,
// compare-to ArrMax01.cmp,
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
set RAM[17] 2050,  // array base
set RAM[18] 5,     // length

set argument[0] 2050,  // pointer to array base
set argument[1] 5,     // length

set RAM[2050] 5,  
set RAM[2051] 9,  
set RAM[2052] 3,  
set RAM[2053] 7,  
set RAM[2054] 2;  

repeat 200 {       
  vmstep;
}
output;
