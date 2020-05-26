# Name: Anden Acitelli
# Assignment: Lab 6
# File: evaluate.s
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "evaluate.s" 

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

    Callee-Saved Registers: 
    %rbx = Caches First Argument (Address of Struct)
    %r12 = Caches Second Argument (Lower Bound) 
    %r13 = Caches Third Argument (Upper Bound)
    %r14 = Caches Count Return Value
    %r15 = Unused 
*/

evaluate: 

    # Save previous function's base pointer and update this one's to the bottom of the stack 
    pushq %rbp  
    movq %rsp, %rbp

    # Pushing all the callee-saved registers that we use (it's our responsibility as a callee to do so)
    pushq %rbx 
    pushq %r12 
    pushq %r13 
    pushq %r14 

    # We need to save these past the first print call, so we shove them in callee saved registers. 
    # It's valid to use caller-saved registers here as well (and I did, before I read that we'd get points off for that, but it was good experience), but that 
    # introduces a lot of overhead insofar as needing to push/pop each one around the function calls. Callee saved registers are *way* cleaner here. 
    movq %rdi, %rbx # Move address of struct into rbx 
    movq %rsi, %r12 # Move lower bound into r12 
    movq %rdx, %r13 # Move upper bound into r13 

    # Setting up print() function parameters and call it 
    movq $.LC0, %rdi # First parameter is the format string, defined above
    movq %rbx, %rsi # Second parameter is our struct string, which conveniently starts at the same memory address as the overall struct
    movq %r12, %rdx # Third parameter is the lower bound 
    movq %r13, %rcx # Fourth parameter is the upper bound 
    xorq %rax, %rax # Zero out the return value before print calls 
    call print # Actually transfer control to print() 

    # Setting up count() function parameters and call it 
    movq %rbx, %rdi # First parameter is the overall address of the struct 
    movq %r12, %rsi # Second parameter is the lower bound 
    movq %r13, %rdx # Third parameter is the upper bound 

    call count # Actually transfer control to count()

    # We need to save %rax through the next call. 
    # We can't use any of the three callee-saved registers we already use, as we need to save their values to restore at the end of the function. So, we use a new one. 
    movq %rax, %r14

    # Setting up print() function parameters (printing out a slightly different string this time, so we switch the third parameter relative to the first print() call) 
    movq $.LC1, %rdi # First argument is the format string
    movq %rax, %rsi # Second argument is the actual return value of count (can either use %rax or %r14 here, doesn't matter) 
    movq %r12, %rdx # Third parameter is the lower bound 
    movq %r13, %rcx # Fourth parameter is the upper bound 
    xorq %rax, %rax # Zero out the return value before print calls 
    call print # Actually transfer control to print()

    # Move our value of %rax obtained from count() back into %rax, seeing as print overwrote it 
    movq %r14, %rax 

    # Restoring callee-saved registers that we use (backwards relative to original push order b/c stack is LIFO, not FIFO)
    popq %r14 
    popq %r13 
    popq %r12 
    popq %rbx 

    # Restore stack frame of function this function was callee of 
    movq %rbp, %rsp 
    popq %rbp 
    ret # Transfer control back to caller function 

    # Assembler directive that essentially means "mark off this amount of space for this function"
    .size evaluate, .-evaluate
