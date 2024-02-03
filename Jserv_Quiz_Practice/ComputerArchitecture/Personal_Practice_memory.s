.data
str:      .string "Print the result : "
newline:  .string "\n"

.data
array:
    .word 1
    .word 2
    .word 3
    .word 4
    .word 5

.text
main:
    la t1, array
    lw t2, 0(t1)
    lw t3, 4(t1)
    lw t4, 8(t1)
    lw t5, 12(t1)
    lw t6, 16(t1)
    mv a1, t2
    mv a2, t3
    mv a3, t4
    mv a4, t5
    mv a5, t6
    jal ra, printResult

    # Exit program
    li a7, 10
    ecall

# --- printResult ---
# a0: Value which factorial number was computed from
# a1: Factorial result
printResult:
    # Get the register which need to be printed
    mv t0, a0
    mv t1, a1
    mv t2, a2
    mv t3, a3
    mv t4, a4
    mv t5, a5
    # Define a0 from .data
    la a0, str
    li a7, 4
    ecall
        
    # print number
    mv a0, t1
    li a7, 1
    ecall
    mv a0, t2
    li a7, 1
    ecall
    mv a0, t3
    li a7, 1
    ecall
    mv a0, t4
    li a7, 1
    ecall
    mv a0, t5
    li a7, 1
    ecall
        
    la a0, newline
    li a7, 4
    ecall
        
    ret