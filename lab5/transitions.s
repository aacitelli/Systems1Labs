# Name: Anden Acitelli
# Assignment: Lab 5
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "transitions.s" 
.data 

.text

/* Register List: 
    %rax: Return Value (in our case this is the current sum of 0->1 shifts)
    %rbp: Base pointer (points to the memory at the beginning of the function) 
    %rsp: Stack Pointer (always points to the lowermost address in the stack) 
    %rdi: The first parameter (the number we're counting the bits of in this context)
    %rsi: Used to hold the increment bit in its smallest position
    %rdx: The traveling bit 
    %rcx: Used to hold one over from the traveling bit 

    No other registers used I think. 
*/

/* 
    Overall Algorithm: 

    Iterate through each bit from right to left. 

    If the current bit ANDed with our shifted bit is one AND the bit one to the right ORed with zero is zero, we add to %rax. This is 
    essentially a really hacky way to use the `test` opcode but with an OR. 
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

    # We start at zero 
    xorq %rsi, %rsi

    # Traveling bit (starts with the 1 bit shifted one over b/c rightmost bit doesn't matter for decision making)
    movq $2, %rdx 

loop_start: 

    # If this sets the z-bit, then the number does NOT have a one in that position. 
    # So, if the z-bit ISN'T set, then the number DOES have a one in that position
    testq %rdx, %rdi

    # If the bit was set, jump over the "bit wasn't set and was therefore one" loop and go on to increment the traveling, etc. 
    jz regardless 
    
if_current_bit_is_one: 
    
    # Get a number that has a one in the position one to the right of the current signed bit 
    shrq %rdx 
    movq %rdx, %rcx 
    shlq %rdx 

    # Invert the number itself so we can use test to see if there's a zero in the one-right-from-current position
    not %rdi 

    # Use test to set the z-bit 
    test %rdi, %rcx 

    # Invert the number itself back (doesn't matter if we invert the one-shifted number back here, as we don't use it again until the next shift ) 
    not %rdi 
    not %rcx # Don't technically need to do this but here we are 

    # If the z-bit ISN't set here, then the number DOES have a zero in the second-to-last position and we have found a '10'. 
    # So, conditionally add to %sil here, then add it to %rax regardless. If we didn't find a `10` rax will just have 0 added to it, 
    # so no harm done. 
    setne %sil 
    addq %rsi, %rax
    
regardless: 

    # We shift the traveling bit regardless, then only shift back to the beginning if the shift didn't cause an overflow.
    shlq %rdx 
    jne loop_start 

done: 

    # Move the stack pointer back to the beginning of this function 
    movq %rbp, %rsp 

    # Pops the thing currently at the top of the stack (the rbp value we saved in the first line of the function) back into rbp
    # This effectively places us back in the stack frame of the function that called this one  
    popq %rbp 

    # Transfers execution back to the calling function 
    ret

    .size transitions, .-transitions
