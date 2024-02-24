# CLZ

.org 0
# Provide program starting address to linker
.global _start

# newlib system calls
.set SYSEXIT,  93
.set SYSWRITE, 64

.section .rodata
str:      .string "MSB: "
          .set str_size, .-str
newline:  .string  "\n"
          .set newline_size, .-newline
mask1:    .dword  0x55555555
mask2:    .dword  0x33333333
mask3:    .dword  0x0f0f0f0f
mask4:    .word   0x7f

.data
array:
    .word 16
    .word 33
    .word 108
res:      .string "Print"
          .set res_size, .-res

.text
_start:
    li s0, 0
    li s1, 3
    la s2, array
    li s3, 64

    # dummy test for jal instruction
.L1:
    jal x0, .L2
.L2:
    nop

loop:
    bge s0, s1, end   # If(s0 >= s1) leave
    lw a1, 0(s2)
    jal ra, count_leading_zeros
    addi s2, s2, 4
    addi s0, s0, 1    # Update s0 = s0 + 1
    j loop            # Go to 1 front

end:
    # Exit program
    li a7, SYSEXIT
    add a0, x0, 0
    ecall
    
count_leading_zeros:
    # Init stack
    addi sp, sp, -24
    sw t0, 20(sp) # use
    sw t1, 16(sp) # use
    sw t2, 12(sp) # use
    sw t3, 8(sp)  # use
    sw t4, 4(sp)  # use
    sw a1, 0(sp)  # use
    
    mv t0, a1
    
    # x |= (x >> 1)
    srli t1, t0, 1
    or t0, t0, t1
    # x |= (x >> 2)
    srli t1, t0, 2
    or t0, t0, t1
    # x |= (x >> 4);
    srli t1, t0, 4
    or t0, t0, t1  
    # x |= (x >> 8);
    srli t1, t0, 8
    or t0, t0, t1
    # x |= (x >> 16);
    srli t1, t0, 16
    or t0, t0, t1
    # x |= (x >> 32);
    li t2, 32
    srl t1, t0, t2
    or t0, t0, t1
    
    # count ones (population count)
    # x -= ((x >> 1) & 0x55555555)
    srli t1, t0, 1
    li t2, 0x55555555
    and t1, t1, t2
    sub t0, t0, t1
    # x = ((x >> 2) & 0x33333333) + 
    #     (x & 0x33333333)
    srli t1, t0, 2
    li t2, 0x33333333
    and t3, t1, t2 # (x >> 2) & 0x33333333
    and t4, t0, t2 # x & 0x33333333
    add t0, t3, t4
    # x = ((x >> 4) + x) & 0x0f0f0f0f
    srli t1, t0, 4
    li t2, 0x0f0f0f0f
    add t3, t0, t1
    and t0, t3, t2
    # x += (x >> 8)
    srli t1, t0, 8
    add t0, t0, t1
    # x += (x >> 16)
    srli t1, t0, 16
    add t0, t0, t1
    # x += (x >> 32)
    li t2, 32
    srl t1, t0, t2
    add t0, t0, t1
    # 64 - (x & 0x7f)
    li t2, 0x7f
    and t1, t0, t2
    li t3, 64
    sub t0, t3, t1
    
    # Store the result and clean the stack
    sub t0, t3, t0
    mv a3, t0

    # Print
    li a7, SYSWRITE    
    li a0, 1           
    la a1, str         
    li a2, str_size   
    ecall              

    addi a3, a3, 48         # change number to ascii digit
    sw   a3, 0(sp)          # push the result onto the stack
    li   a0, 1              # 1 = standard output (stdout)
    mv   a1, sp             # pass the stack address to a1
    li   a2, 1              # length of value digit
    li   a7, SYSWRITE       # "write" syscall
    ecall
        
    li a7, SYSWRITE    
    li a0, 1           
    la a1, newline         
    li a2, newline_size   
    ecall 

    addi sp, sp, 24
    ret
