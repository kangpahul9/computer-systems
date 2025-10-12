load AddSub.vm,
output-file AddSub02.out,
compare-to AddSub02.cmp,
output-list sp%D1.6.1 local%D1.6.1 argument%D1.8.1 this%D1.6.1 that%D1.6.1
            RAM[16]%D1.6.1 RAM[17]%D1.6.1 RAM[18]%D1.6.1
            local[0]%D1.8.1 local[1]%D1.8.1 local[2]%D1.8.1
            argument[0]%D1.11.1 argument[1]%D1.11.1 argument[2]%D1.11.1;

set sp 256,        // stack pointer
set local 512,     // base address of the local segment
set argument 600,  // base address of the argument segment
set this 3200,     // base address of the this segment
set that 3210,     // base address of the that segment

set RAM[16] 0,     // static 0
set RAM[17] 9999,  // static 1
set RAM[18] -9999, // static 2

set local[0] 32767,   // local 0 (max positive 15-bit)
set local[1] -32768,  // local 1 (max negative 15-bit)
set local[2] 1,       // local 2

set argument[0] 0,    // argument 0
set argument[1] 5000, // argument 1
set argument[2] -5000;// argument 2

repeat 35 {        
  vmstep;
}
output;
