# Name: Anden Acitelli
# Assignment: Lab 5
# File: search.s
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "search.s" 

# Read-only data section (generally for strings, constants, and other immutable data)
.section .rodata 
.LC0: 
    .string "evaluate: Evaluating '%s' looking for results between %ld and %ld.\n"
.LC1: 
    .string "evaluate: Found %ld results between %ld and %ld\n"

# Data we might actually need to change 
.data 

# Required directive of every function 
.globl evaluate

# Denotes that the code actually begins right here 
.text

/* 
    Parameters: 
    %rdi = Address of Structure 
    %rsi = Lower Bound (Inclusive) 
    %rdx = Upper Bound (Inclusive) 
    %rax (Return Value): Stores whatever count returns ezpz 

    Free Registers: 
    Fourth Through Sixth Parameters: 
    %rcx (Fourth Parameter): 
    %r8 (Fifth Parameter): 
    %r9 (Sixth Parameter): Used Temporarily to Cache First Argument before each print() call 

    Other Caller-Saved Registers that I may need to use: 
    %r10: Used Temporarily to Cache Second Argument before each print() call
    %r11: Used Temporarily to Cache Third Argument before each print() call 

    Callee-Saved Registers Used (just means I have to push them at beginning and pop them at the end): 
*/

# TODO: Figure out if my register usage is good here and that I can use caller-saved registers in what's not a leaf function (though I push and pop them beforehand, so I should be good)
search: 

    # Save previous base pointer to stack and set up new base pointer 
    pushq %rbp  
    movq %rsp, %rbp 

    # Restore stack frame of function this function was callee of 
    movq %rbp, %rsp 
    popq %rbp 

    # Transfer control back to caller function 
    ret

    # Assembler directive that essentially means "mark off this amount of space for this function"
    .size search, .-search
