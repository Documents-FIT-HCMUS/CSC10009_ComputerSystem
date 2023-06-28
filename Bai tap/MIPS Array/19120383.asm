.data
arr: .space 400
br: .asciiz "\n"
spc: .asciiz " "
len: .asciiz "Nhap kich thuoc mang (N > 0): "
arrInput: .asciiz "Nhap cac phan tu trong mang:\n"
arrOutput:  .asciiz "Cac phan tu trong mang: "

.text
main:
# Input Array Length
check:
	la $a0, len
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	move $s0, $v0
	blez $s0, check
# Input Array Elements
la $a0, arrInput
li $v0, 4
syscall
li $t1, 0
li $t2, 0
inputLoop:
	li $v0, 5
	syscall
	move $t0, $v0
	sw $t0, arr($t1)
	addi $t1, $t1, 4
	addi $t2, $t2, 1
	bge $t1, 400, endInput
	bge $t2, $s0, endInput
	j inputLoop
endInput:
li $t1, 0
li $t2, 0
# Print Array Elements
la $a0, arrOutput
li $v0, 4
syscall
outputLoop:
	lw $t0, arr($t1)
	move $a0, $t0
	li $v0, 1
	syscall
	la $a0, spc
	li $v0, 4
	syscall
	addi $t1, $t1, 4
	addi $t2, $t2, 1
	bge $t1, 400, endOutput
	bge $t2, $s0, endOutput
	j outputLoop
endOutput:
	
# Print N elements
	Print_Array:
	lw $t0, ($sp)
	addi $sp, $sp, 4
	move $a0, $t0
	li $v0, 1
	syscall
	
	la $a0, spc
	li $v0, 4
	syscall
	
	addi $s1, $s1, 1
	blt $s1, $s0, Print_Array	
