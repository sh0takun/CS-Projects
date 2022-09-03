########################################################################## 
# Created by: Tonari, Shota 
# stonari
# 10 November 2021
# 
# Assignment: Lab 3: ASCII-risks (Asterisks)
# CSE12, Computer Systems and Assembly Language # UC Santa Cruz, Fall 2021 
# 
# Description: This program asks the user to input a number and prints 
# a sequence of embedded numbers and ASCII triangles using loops.  
# Notes: This program is intended to be run from the MARS IDE. 
##########################################################################
# Pseudocode: 
# t1 is placeholder counter (starts from 1)
# s1 is placeholder counter (only 0/1)
# t0 is user's input

# start function prints and asks user's input for height
# uses syscall 5 to read input as int
# moves input to temporary register t0
# if user input is less than or equal to 0, jump to error function
# if not, jump to number loop

# error function prints error message
# jumps back to original start function

# number function iterates until s1 is less than or equal to height
# if t1 becomes larger than t0, then it will terminate program (program is finished)
# uses syscall 1 to print integer
# loops every time the function is called, puts integer on new line

# asterisck and tab loop 
# if s1 is less than t1 (1st placeholder counter) s2 = 1
# if s1 is greater than or equal to t1, s2 = 0
# if s2 is equal to 0, branch to NewLine
# if not, print tab and asterisks
# add 1 to the s1 counter for every loop
# jump back to beginning of loop

# new line function is fundamentally to end the row and print new line
# jump to next function

# next function adds 1 to t1 counter (1st placeholder counter)
# load 1 to s1 to reset the initial value
# jump to number loop to restart process


.data 
Height: .asciiz "Enter the height of the pattern (must be  greater than 0):\n"
Invalid: .asciiz "Invalid Entry!\n"
Test: .asciiz "test"			
Tab: .asciiz "\t"
New_Line: .asciiz "\n"
Asterisks: .asciiz "*"



.text
start:
	li $t1, 1 		# put 1 as placeholder into t1 and s1
	li $s1, 1 
	
	li $v0, 4		# takes user's input using syscall functionality number 4
	la $a0, Height
	syscall	
	
	li $v0, 5 		
	syscall
	
	move $t0, $v0 		# move to t0 to store value
	
	blez $t0, error 	# if the value is less than or equal to 0, moves to error
	
	j Number		#if not, jumps to continue

error:
	li $v0, 4 
	la $a0, Invalid  	# prints Invalid Entry
	syscall
	j start 		# jump will return to start function

Number:  
	sle $s1,$t1,$t0 	#s1=1 if $t1<=t0	
				#s1=0 if $t1>t0		
	beq $s1,$zero, Exit	#if s1 is zero, exit
	 				
	li $v0,1		# syscall 1 to print integer		
	move $a0,$t1 				
	syscall	
		
Check:  
	slt $s2,$s1,$t1 	#s2=1 if $s1 < $t1	
		
	beq $s2,$zero, NewLine 	
	j Asterisk_Tab

Asterisk_Tab:	
	li $v0,4		# prints tab between elements of triangle
	la $a0, Tab
	syscall 
	
	li $v0,4
	la $a0, Asterisks	# prints * symbol
	syscall
	
	addi $s1,$s1,1 		# increment value of $s1 to 1
	j Check			# keeps on looping
	
NewLine: 	
	li $v0,4
	la $a0, New_Line 	# prints new line
	syscall
	j Next
	
Next:	addi $t1,$t1,1 		# increment $t1 value with 1
	li $s1,1 		# set $s1 to initial value
	j Number		# jump to initial loop (number)
	
Exit: 	li $v0,10 		# syscall 10 to terminate program
	syscall
	


	
	
	
	

	
