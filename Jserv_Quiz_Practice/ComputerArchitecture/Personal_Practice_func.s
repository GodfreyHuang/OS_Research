#.global add_val
#.global add_sub_val

.data
str:      .string "Print the result : "
newline:  .string "\n"
input1:   .word   20

.text
main:
    lw a1 input1
    jal ra, add_val
    jal ra, printResult

    jal ra, add_sub_val
    jal ra, printResult

    # Exit program
    li a7, 10
    ecall

# --- add_val ---
add_val:
    addi sp, sp, -4
    sw a1 0(sp)
    addi a1, a1, 1
    addi sp, sp, 4
    ret

add_sub_val:
    # init stack which function need
    addi sp, sp -32
    sw s1, 28(sp)
    sw s2, 24(sp)
    sw s3, 20(sp)
    sw s4, 16(sp)
    sw s0, 12(sp)
    sw t1, 8(sp)
    sw t2, 4(sp)
    sw a1, 0(sp)
    # do (15 + 16) - (5 + 6) = 20
    li s1, 15
    li s2, 16
    li s3, 5
    li s4, 6
    add t1, s3, s4
    add t2, s1, s2
    sub s0, t2, t1
    # load s0 to a1
    mv a1, s0
    # release memory space of the function
    addi sp, sp 32
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