.data
	
inputN: .asciiz "Nhap N: "
sum_result: .asciiz "Tong la: "
br: .asciiz "\n"
spc: .asciiz " "

.text
main:
	# Input N, store at $s0
	Input_N:
	la $a0, inputN
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	move $s0, $v0
	blez $s0, Input_N
	
	# Use $s1 as index, start at 0, +1 each time
	li $s1, 0
	
	# Input N elements
	Input_Array:
	li $v0, 5
	syscall
	move $t0, $v0
	
	addi $sp, $sp, -4
	sw $t0, ($sp)
	addi $s1, $s1, 1
	blt $s1, $s0, Input_Array
	jal calculate_sum
	jal print_sum
	
exit:
	li $v0, 10
	syscall
		
calculate_sum:
	# Store result in $t0
	li $t0, 0
	# Use $s1 as index, start at 0, +1 each time
	li $s1, 0
	# Loop to calculate sum
	Sum_Loop:
	lw $t1, ($sp)
	addi $sp, $sp, 4
	add $t0, $t0, $t1
	addi $s1, $s1, 1
	blt $s1, $s0, Sum_Loop
	
	jr $ra
	
print_sum:
	la $a0, sum_result
	li $v0, 4
	syscall
	
	move $a0, $t0
	li $v0, 1
	syscall
	
	jr $ra
	
	
