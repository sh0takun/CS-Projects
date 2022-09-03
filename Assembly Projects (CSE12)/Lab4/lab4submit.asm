########################################################################## 
# Created by: Tonari, Shota 
# stonari
# 30 November 2021
# 
# Assignment: Lab 4: Functions and Graphs
# CSE12, Computer Systems and Assembly Language # UC Santa Cruz, Fall 2021 
# 
# Description: This program needs to be directly used with the lab4 test file. 
# In this program, you will use MIPS memory-map IO, macros, and stack to draw
# crosshairs and pixels with different colors inputted by the test file. 
##########################################################################

# Pseudocode
# getCoordinate: takes 0x000000ff as a placeholder, and replaces the input y coords into ff. 
# 		 shifts right logic by 16 for x coords. 
# formatCoordinates: shifts the x coord by 16 using shift left logic
#		     combines the y coord into final output coords
# getPixelAddress; does exactly what its told: multiply y input by 128
# 		   takes that output and adds x input, multiply that by 4
#		   lastly, combine the output with origin Address which is
#		   0xffff0000. Eq: output = origin + 4 * (%output %x %y) 
# clearbitmap/bitmap_loop: put origin address (0,0) into register t0; put the last pixel 128 into t1
#	       there are 128x128 pixels; loop and clear bitmap until the counter subtracts
#	       from 128. After the counter hits threshold; branch
# draw_pixel: call getCoordinate, getPixelAddress, and sets value in memory to the color according to pixel and color of pixel
# get_pixel: call getCoordinate, getPixelAddress, returns pixel color
# draw_horizontal_line: call getPixelAddress, run loop until counter hits 0 from 127 pixels
#			when counter hits 0, branch to end_loop which returns function
# draw_vertical_line: same as horizontal, add 512 to t2 register, branch when counter hits 0 to end loop.
# draw_crosshair: draw vertical and horizontal crosshair given (x, y)
#		  push registers ra, t0 (cords), t6 (RGB) 
#		  move registers into placeholder registers
#		  call getCoordinates, push and pop register to save values, call getPixelAddress, do same
#		  call draw_horizontal_line and draw_vertical_line
#		  return

# Spring 2021 CSE12 Lab 4 Template
######################################################
# Macros made for you (you will need to use these)
######################################################

# Macro that stores the value in %reg on the stack 
#	and moves the stack pointer.
.macro push(%reg)
	subi $sp $sp 4
	sw %reg 0($sp)
.end_macro 

# Macro takes the value on the top of the stack and 
#	loads it into %reg then moves the stack pointer.
.macro pop(%reg)
	lw %reg 0($sp)
	addi $sp $sp 4	
.end_macro

#################################################
# Macros for you to fill in (you will need these)
#################################################

# Macro that takes as input coordinates in the format
#	(0x00XX00YY) and returns x and y separately.
# args: 
#	%input: register containing 0x00XX00YY
#	%x: register to store 0x000000XX in
#	%y: register to store 0x000000YY in
.macro getCoordinates(%input %x %y)
	and %y, %input, 0x000000ff
	srl %x, %input, 16
.end_macro

# Macro that takes Coordinates in (%x,%y) where
#	%x = 0x000000XX and %y= 0x000000YY and
#	returns %output = (0x00XX00YY)
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%output: register to store 0x00XX00YY in
.macro formatCoordinates(%output %x %y)
	sll %output, %x, 16
	add %output, %output, %y
.end_macro 

# Macro that converts pixel coordinate to address
# 	  output = origin + 4 * (x + 128 * y)
# 	where origin = 0xFFFF0000 is the memory address
# 	corresponding to the point (0, 0), i.e. the memory
# 	address storing the color of the the top left pixel.
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%output: register to store memory address in
.macro getPixelAddress(%output %x %y)
	# YOUR CODE HERE
	mul %output, %y, 128
	add %output, %output, %x
	mul %output, %output, 4
	add %output, %output, 0xffff0000
.end_macro

.text
# prevent this file from being run as main
li $v0 10 
syscall

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#*****************************************************
# Clear_bitmap: Given a color, will fill the bitmap 
#	display with that color.
# -----------------------------------------------------
# Inputs:
#	$a0 = Color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
clear_bitmap: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	push($t0)
	push($t1)
	
	li $t0, 0xffff0000
	li $t1, 128 
	mul $t1, $t1, 128 
	
bitmap_loop: 
	sw $a0, ($t0) 
	addi $t0, $t0, 4 
	subi $t1, $t1, 1
	bgtz $t1, bitmap_loop
	
	pop($t1)
	pop($t0)
	
 	jr $ra

#*****************************************************
# draw_pixel: Given a coordinate in $a0, sets corresponding 
#	value in memory to the color given by $a1
# -----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#		$a1 = color of pixel in format (0x00RRGGBB)
#	Outputs:
#		No register outputs
#*****************************************************
draw_pixel: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	push($t0)
	push($t1)
	push($t2)
	

	getCoordinates($a0, $t0, $t1)
	getPixelAddress($t2, $t0, $t1)
	sw $a1, ($t2)
	
	pop($t2)
	pop($t1)
	pop($t0)
	jr $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#	Outputs:
#		Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
get_pixel: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	push($t0)
	push($t1)
	push($t2)
	
	getCoordinates($a0, $t0, $t1)
	getPixelAddress($t2, $t0, $t1) 
	
	lw $v0, ($t2)

	pop($t2)
	pop($t1)
	pop($t0)
	
	jr $ra

#*****************************************************
# draw_horizontal_line: Draws a horizontal line
# ----------------------------------------------------
# Inputs:
#	$a0 = y-coordinate in format (0x000000YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_horizontal_line: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	push($t1)
	push($t2)
	
	getPixelAddress($t2, $t1, $a0)		
	
	li $t3, 127				#counter starting from 128 bc it is 128 pixels tall			
	
	hori_loop:
	blt $t3, 0, end_loop			#jump to end loop if counter hits 0
	sw $a1, ($t2)
	add $t2, $t2, 4
	subi $t3, $t3, 1			#subtract counter by 1
	
	j hori_loop
	
	end_loop:

	pop($t2)
	pop($t1)

 	jr $ra
 	
#*****************************************************
# draw_vertical_line: Draws a vertical line
# ----------------------------------------------------
# Inputs:
#	$a0 = x-coordinate in format (0x000000XX)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_vertical_line: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	push($t1)
	push($t2)
	
	getPixelAddress($t2, $a0, $t1)		
	
	li $t3, 127				#counter starting from 128 bc it is 128 pixels tall			
	
	verti_loop:	
	sw $a1, ($t2)
	add $t2, $t2, 512
	subi $t3, $t3, 1			#subtract counter by 1
	blt $t3, 0, endSecond_loop		#jump to end loop if counter hits 0
		
	j verti_loop
	
	endSecond_loop:

	pop($t2)
	pop($t1)

 	jr $ra

#*****************************************************
# draw_crosshair: Draws a horizontal and a vertical 
#	line of given color which intersect at given (x, y).
#	The pixel at (x, y) should be the same color before 
#	and after running this function.
# -----------------------------------------------------
# Inputs:
#	$a0 = (x, y) coords of intersection in format (0x00XX00YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
# HINT: Store the pixel color at $a0 before drawing the horizontal and 
	# vertical lines, then afterwards, restore the color of the pixel at $a0 to 
	# give the appearance of the center being transparent.
	
	# Note: Remember to use push and pop in this function to save your t-registers
	# before calling any of the above subroutines.  Otherwise your t-registers 
	# may be overwritten.  
draw_crosshair: nop
    push($ra)
    push($t0)					#t0 is placeholder for cords from a0
    push($t6)					#t6 is placeholder for RGB color in format
    
    move $t0 $a0  
    move $t6 $a1 
    					
    move $t5 $sp				#initialize stack pointer


    getCoordinates($a0 $t2 $t3) 		#call get-coordinate function to put in coordinate form
    

    push($t3) 					#push x value
    getPixelAddress($a2, $t2, $t3) 		
    pop($t3)

    lw $t4, ($a2) 
    push($a2)
    

    move $a0, $t3 
    move $a1, $t6 
    jal draw_horizontal_line
    

    move $a0, $t2
    move $a1, $t6 
    jal draw_vertical_line
    
    pop($a2)					
    sw $t4, ($a2)
    
    move $sp $t5				#move stack pointer

    pop($t6)
    pop($t0)
    pop($ra)
    jr $ra



