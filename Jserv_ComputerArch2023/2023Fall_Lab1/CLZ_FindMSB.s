.data
argument: .word   0
str:      .string "MSB: "
newline:  .string  "\n"
mask1:    .dword  0x5555555555555555
mask2:    .dword  0x3333333333333333
mask3:    .dword  0x0f0f0f0f0f0f0f0f
mask4:    .word   0x7f

.data
array:
    .word 16
    .word 33
    .word 108

.text
main:
    li s0, 0
    li s1, 3
    la s2, array
    li s3, 64
1:
    bge s0, s1, 1f   # If(s0 >= s1) leave
    lw a1, 0(s2)
    jal count_leading_zeros
    sub a1, s3, a1
    jal printResult
    addi s2, s2, 4
    addi s0, s0, 1   # Update s0 = s0 + 1
    j, 1b            # Go to 1 front
1:
    # Exit program
    li a7, 10
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
    # x -= ((x >> 1) & 0x5555555555555555)
    srli t1, t0, 1
    lw t2, mask1
    and t1, t1, t2
    sub t0, t0, t1
    # x = ((x >> 2) & 0x3333333333333333) + 
    #     (x & 0x3333333333333333)
    srli t1, t0, 2
    lw t2, mask2
    and t3, t1, t2 # (x >> 2) & 0x3333333333333333
    and t4, t0, t2 # x & 0x3333333333333333
    add t0, t3, t4
    # x = ((x >> 4) + x) & 0x0f0f0f0f0f0f0f0f
    srli t1, t0, 4
    lw t2, mask3
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
    add, t0, t0, t1
    # 64 - (x & 0x7f)
    lw t2, mask4
    and t1, t0, t2
    li t3, 64
    sub t0, t3, t1
    
    # Store the result and clean the stack
    mv a1, t0
    addi sp, sp, 24
    ret

# --- printResult ---
# a0: Value which factorial number was computed from
# a1: Factorial result
printResult:
    # Get the register which need to be printed
    mv t0, a0
    mv t1, a1
        
    # Define a0 from .data
    la a0, str
    li a7, 4
    ecall
        
    # move t1 to a0 and print value
    mv a0, t1
    li a7, 1
    ecall
        
    la a0, newline
    li a7, 4
    ecall
        
    ret