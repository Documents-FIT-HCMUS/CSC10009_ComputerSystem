.data
p1: .asciiz "Nhap so A: "
p2: .asciiz "Nhap so B: "
result1: .asciiz "A + B: "
result2: .asciiz "A - B: "
result3: .asciiz "A * B: "
result4: .asciiz "A / B: "
result5: .asciiz "A % B: "
br: .asciiz "\n"
.text
.globl main
main:
# Input first numbers
la $a0, p1
addi $v0, $0, 4
syscall
addi $v0, $0, 5
syscall
add $s0, $0, $v0
la $a0, p2
addi $v0, $0, 4
syscall
addi $v0, $0, 5
syscall
add $s1, $0, $v0
# Calculate addition
la $a0, result1
addi $v0, $0, 4
syscall
add $a0, $s0, $s1
addi $v0, $0, 1
syscall
# Print line break
la $a0, br
addi $v0, $0, 4
syscall
# Calculate subtraction
la $a0, result2
addi $v0, $0, 4
syscall
sub $a0, $s0, $s1
addi $v0, $0, 1
syscall
# Print line break
la $a0, br
addi $v0, $0, 4
syscall
# Calculate multiplication
la $a0, result3
addi $v0, $0, 4
syscall
mul $a0, $s0, $s1
addi $v0, $0, 1
syscall
# Print line break
la $a0, br
addi $v0, $0, 4
syscall
# Calculate division
div $s2, $s0, $s1
mflo $t1
mfhi $t2
# Print result
la $a0, result4
addi $v0, $0, 4
syscall
add $a0, $0, $t1
addi $v0, $0, 1
syscall
# Print line break
la $a0, br
addi $v0, $0, 4
syscall
# Print modulo
la $a0, result5
addi $v0, $0, 4
syscall
add $a0, $0, $t2
addi $v0, $0, 1
syscall
