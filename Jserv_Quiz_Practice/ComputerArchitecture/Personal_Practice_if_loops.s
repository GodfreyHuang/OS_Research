.data
str:      .string "Print the result : "
newline:  .string "\n"
i:        .word 15
j:        .word 13
a:        .word 1
b:        .word 3
    
.text
main:
    # Load words
    lw s0, i
    lw s1, j
    lw s2, a
    lw s3, b
    
    # Do If else
    beq s0, s1, then #if(i == j), jump to then: 
                     # Can change to another brand instructions
    else:
    sub s2, s2, s3
    j end
    then:
    add s2, s2, s3
    end:
        
    # Print
    mv a1, s2
    jal ra, printResult
    
    #----------------
    # Do for loop
    jal ra, func1
    jal ra, printResult
    
    # Exit program
    li a7, 10
    ecall
    
func1:
    addi sp, sp, -20
    sw s0, 16(sp)
    sw s1, 12(sp)
    sw s2, 8(sp)
    sw s3, 4(sp)
    sw a1, 0(sp)
    
    li s0, 0
    li s1, 3
    lw s2, a
    lw s3, b
1:
    bge s0, s1, 1f # If(s0 >= s1) leave
    sll s3, s3, s2 # s3 = s3 << s2
    addi s0, s0, 1 # Update s0 = s0 + 1
    j, 1b          # Go to 1 front
1:
    mv a1, s3      # mv s3 to a1
    addi sp, sp, 20
    ret  

printResult:
    # Get the register which need to be printed
    # The registers are a0, a1
    # a0 use to print string; a1 use to print number
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