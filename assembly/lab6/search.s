# Name: Anden Acitelli
# Assignment: Lab 6
# File: search.s
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "search.s" 

# Read-only data section (generally for strings, constants, and other immutable data)
.section .rodata 
.LC0: 
    .string "search: '%s' has the most results between %ld and %ld with %ld found.\n"

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

    # Eight byte local variable used as pointer to track address of struct that had best evaluate result
    # Located at 0-byte offset from %rbp 
    # Because 16 mod 16 is 0, we don't need to worry about stack alignment (?)
    # First 8 bytes are pointer to address of best struct (40 + 0 offset)
    # Second 8 bytes are actual result of the best call (40 + 8 offset) 
    sub $16, %rsp

    # We're gonna need every callee-saved register in here for sure, so we push these before
    pushq %rbx 
    pushq %r12 
    pushq %r13 
    pushq %r14 
    pushq %r15 

    # By default, the first struct is the best one 
    movq %rdi, %r8 # Have to move it to a different, unused register; Original %rdi is used later 
    movq (%r8), %r8 # Dereferencing the pointer to the pointer to the first struct 
    movq %r8, -8(%rbp) # Store pointer to the first struct that we just obtained in the first local variable 

    # By default, best value is zero
    movq $0, -16(%rbp)

    # We'll be making calls to evaluate a LOT, and will need to change our parameter registers for that, so we need to store our parameters in callee-saved registers
    movq %rdi, %rbx # Store pointer to array of struct pointers in %rbx 
    movq %rsi, %r12 # Store number of structs in %r12 
    movq %rdx, %r13 # Store lower bound in %r13 
    movq %rcx, %r14 # Store upper bound in %r14 
    
    # Keeps track of the index of whichever index of the array we're on 
    xorq %r15, %r15 # Zeroing this out, b/c we start on the 0th index 

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
        leaq (%rbx, %r15, 8), %rdi # We load the address of a pointer to our current struct into %rdi
        movq (%rdi), %rdi # We then dereference that address of a pointer to our current struct to get a pointer to our current struct, and put it in %rdi. Evaluate takes the address of the struct as its first argument.  
        movq %r13, %rsi # Put lower bound in second parameter
        movq %r14, %rdx # Put upper bound in third parameter 
        xorq %rax, %rax # Zero out %rax before calls 
        call evaluate # Actually do the call 

        # Way too many memory hits ahead, don't vomit on the code in disgust please 

        # If cmpq(newReturn, oldBest) is negative, we have a new best result. 
        cmpq %rax, -16(%rbp) # Our saved "best result" is at 0-byte offset from base pointer
        
        # If our result wasn't negative (i.e. wasn't our new best result) skip over reassignments 
        js is_new_best_result
        jmp skip_is_new_best_result

        is_new_best_result: 

            # If cmpq (newReturn, oldBest) is negative, we have a new best.
            movq %rax, -16(%rbp) # Update our actual best count to whatever the function returned 

            # Grabbing the actual pointer to the struct via the same method of leaq + dereference done above 
            leaq (%rbx, %r15, 8), %rdi # Getting address of pointer to our struct
            movq (%rdi), %rdi 
            movq %rdi, -8(%rbp) # Dereferencing and saving in our local variable, which is O-offset is the actual space for our pointer

        # This label is skipped directly to if it's not the best result
        # This isn't the best name, seeing as the new best result logic chain technically goes here too, but I wanted to preserve the 
        # naming contrast I've got going here, and this long comment here explains it well enough that it's not ambiguous 
        skip_is_new_best_result: 

        inc %r15 # Increment index we're on of array 
        jmp loop_start # Unconditionally jump back to start; It's a while loop, not a do/while loop 

    done_with_loop: 

    # Set up a call to print, and actually print out our best value 
    movq $.LC0, %rdi # First argument is the format string itself 
    movq -8(%rbp), %rsi # Second argument is the name of the struct, though the beginning of the struct is the same in context to our program 
    movq %r13, %rdx # Third argument is the lower bound 
    movq %r14, %rcx # Fourth argument is the upper bound 
    movq -16(%rbp), %r8 # Fifth argument is the number of things found 
    xorq %rax, %rax # %rax needs zeroed out before a print call 
    call print # Actually do the function call 

    # Actually put pointer to our best value in %rax, now that we're done with all function calls 
    movq -8(%rbp), %rax 

    # Gotta pop all our callee-saved register values back into their registers (in reverse order of how we pushed, b/c stack is LIFO)
    popq %r15 
    popq %r14 
    popq %r13 
    popq %r12 
    popq %rbx 

    # Revert stack modifications due to stack space 
    add $16, %rsp 

    # Restore stack frame of function this function was callee of 
    movq %rbp, %rsp 
    popq %rbp 
    ret # Transfer control back to caller function 

    # Assembler directive that essentially means "mark off this amount of space for this function"
    .size search, .-search
