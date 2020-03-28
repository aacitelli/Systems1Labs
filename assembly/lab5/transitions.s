# Name: Anden Acitelli
# Assignment: Lab 5
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "transitions.s" 
.text

/* Register List: 
    %rax: Return Value (in our case this is the current sum of 0->1 shifts)
    %rbp: Base pointer (points to the memory at the beginning of the function) 
    %rsp: Stack Pointer (always points to the lowermost address in the stack) 
    %rdi: The first parameter (the number we're counting the bits of in this context)
    %%rsi, %rdx: First, second, third parameters. We'll use them to hold values. 
    %
*/

.global transitions
transitions: 

    # rbp = 64-bit Base Pointer
    # Save the calling function's base pointer so we can return to that offset (instead of the one we are about to create) at the end of this function 
    pushq %rbp

    # Save the current stack pointer into the base pointer so that we have the offset saved for this specific function  
    movq %rsp, %rbp 

    # We start at zero 0->1 shifts, then start summing
    xorq %rax, %rax 

    # Zero the two parameters we'll use to store the two relevant bits 
    xorq %rsi, %rsi 
    xorq %rdx, %rdx 

    # If the number's already through, jump to done

loop: 

    /* 
    # Do everything here!
    % rsi: Used to hold our "current" value 
    % rdi: Used to hold our "next" value 

    % Grab first two bits before the loop actually starts 


    loop_start: 

        # Move the next bit into the current bit 


        # Grab the new next bit 

        # Grab the next bit 

        # If next bit minus current bit == 1, then we have a shift! Increment RAX by 1 

        # If condition mandates we still have bits to read, jump back to loop 
    */

done: 

    movq $5, %rax
    
    # Move the stack pointer back to the beginning of this function 
    movq %rbp, %rsp 

    # Pops the thing currently at the top of the stack (the rbp value we saved in the first line of the function) back into rbp
    # This effectively places us back in the stack frame of the function that called this one  
    popq %rbp 

    # Transfers execution back to the calling function 
    ret
