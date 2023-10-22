# Initialize registers
    .data
num1:   .word 5
num2:   .word 2
result: .word 0

    .text
    .globl main
main:
    lw $t0, num1     # Load num1 into $t0
    lw $t1, num2     # Load num2 into $t1
    li $t2, 0        # Initialize $t2 as a counter
    li $t3, 10       # Set the loop count to 10

loop:
    add $t0, $t0, $t1  # Add num2 to num1
    sub $t1, $t1, $t0  # Subtract num1 from num2

    # Store the result and update the counter
    sw $t0, result
    addi $t2, $t2, 1

    # Check loop condition
    bne $t2, $t3, loop

    # Exit the program
    li $v0, 10
    syscall
