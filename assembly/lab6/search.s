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

# Data we might actually need to change 
.data 

# Required directive of every function 
.globl search

# Denotes that the code actually begins right here 
.text

/* 
    Parameters: 
    %rdi (First Parameter): Array of pointers to struct
    %rsi (Second Parameter): Number of structs
    %rdx (Third Parameter): Lower Bound
    %rcx (Fourth Parameter): Upper Bound

    Callee-Saved Registers: 
    %rbx = Caches First Argument (Array of pointers to struct)
    %r12 = Caches Second Argument (Number of structs) 
    %r13 = Caches Third Argument (Lower Bound)
    %r14 = Caches Fourth Argument (Upper Bound)
    %r15 = Holds Index of Array
*/

search: 

    # Save previous base pointer to stack and set up new base pointer 
    pushq %rbp  
    movq %rsp, %rbp 

    # We're gonna need every callee-saved register in here for sure, so we push these before
    pushq %rbx 
    pushq %r12 
    pushq %r13 
    pushq %r14 
    pushq %r15 

    # We'll be making calls to evaluate a LOT, and will need to change our parameter registers for that, so we need to store our parameters in callee-saved registers
    movq %rdi, %rbx # Store pointer to array of struct pointers in %rbx 
    movq %rsi, %r12 # Store number of structs in %r12 
    movq %rdx, %r13 # Store lower bound in %r13 
    movq %rcx, %r14 # Store upper bound in %r14 
    
    # Keeps track of the index of whichever index of the array we're on 
    xorq %r15, %r15 # Zeroing this out, b/c we start on the 0th index 

break: 

    # I'm tryna figure out how to do it with 5 because I learn from that, but 
    # I'm also trying to do it with 6+ so I understand how to do local variables 

    # Loop through each struct, updating whichever was the best one 
    loop_start: 

        # If our current index is past the end of our array, get out of the loop b/c this is an invalid index 
        # %rsi = Number of Structs
        # %rdi = Current Index
        # So, if cmpq (NumberOfStructs, CurrentIndex) is nonnegative, we're not on our structs any more and we get out of the loop 
        cmpq %r12, %r15
        jns done_with_loop 

        # Filling parameters for our upcoming evaluate() call 
        leaq (%rbx, %r15, 8), %rdi # Put the address of the current struct in as the first parameter
        movq %r13, %rsi # Put lower bound in second parameter
        movq %r14, %rdx # Put upper bound in third parameter 
        xorq %rax, %rax # Zero out %rax before calls 
        call evaluate # Actually do the call 

        inc %r15 # Increment index we're on of array 
        jmp loop_start # Unconditionally jump back to start; It's a while loop, not a do/while loop 

    done_with_loop: 

    # Set up a call to print, and actually print out our best value 

    # Gotta pop all our callee-saved register values back into their registers (in reverse order of how we pushed, b/c stack is LIFO)
    pushq %r15 
    pushq %r14 
    pushq %r13 
    pushq %r12 
    pushq %rbx 

    # Restore stack frame of function this function was callee of 
    movq %rbp, %rsp 
    popq %rbp 
    ret # Transfer control back to caller function 

    # Assembler directive that essentially means "mark off this amount of space for this function"
    .size search, .-search
