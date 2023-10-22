.data
loop_count: .word 10
result: .word 0

.text
.globl main

main:
    lw $t0, loop_count  # Load the loop count
    li $t1, 0           # Initialize a counter
    li $t2, 1           # Initialize value to be added in each iteration

loop:
    # Unrolled loop iteration 1
    add $t1, $t1, $t2
    sw $t1, result

    # Display the updated $t1 value
    move $a0, $t1
    li $v0, 1
    syscall

    # Unrolled loop iteration 2
    add $t1, $t1, $t2
    sw $t1, result

    # Display the updated $t1 value
    move $a0, $t1
    li $v0, 1
    syscall

    # Increment the counter
    addi $t0, $t0, -2

    # Check loop condition
    bnez $t0, loop  # Branch back to the loop if $t0 is not zero

    # Exit the program
    li $v0, 10
    syscall
