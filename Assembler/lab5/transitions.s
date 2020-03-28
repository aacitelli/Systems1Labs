# Name: Anden Acitelli
# Assignment: Lab 5
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "transitions.s" 

/* Register List: 
    %rax: Return Value (in our case this is the current sum of 0->1 shifts)
    %rbp: Base pointer (points to the memory at the beginning of the function) 
    %rsp: Stack Pointer (always points to the lowermost address in the stack) 
    %rdi, %rsi, %rdx: First, second, third parameters 
*/
countBits: 

    # rbp = 64-bit Base Pointer
    # Save the calling function's base pointer so we can return to that offset (instead of the one we are about to create) at the end of this function 
    pushq %rbp

    # Save the current stack pointer into the base pointer so that we have the offset saved for this specific function  
    movq %rsp, %rbp 

    # We start at zero 0->1 shifts, then start summing
    xorq %rax, %rax 

    # Do everything here!
    loop_start: 



    # Move the stack pointer back to the base pointer of this function 
    movq %rbp, %rsp 

    # Pops the thing currently at the top of the stack (the rbp value we saved in the first line of the function) back into rbp
    # This effectively places us back in the stack frame of the function that called this one  
    popq %rbp 

    # Transfers execution back to the calling function 
    ret