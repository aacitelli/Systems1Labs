# Name: Anden Acitelli
# Assignment: Lab 5
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

    Free Registers: 
    Fourth Through Sixth Parameters: 
    %rcx (Fourth Parameter): Not passed-in, but we use this to pass in an argument to print 
    %r8 (Fifth Parameter): As of yet unused
    %r9 (Sixth Parameter): As of yet unused

    Other Caller-Saved Registers that I may need to use: 
    %r10: As of yet unused
    %r11: As of yet unused

    Callee-Saved Registers Used (just means I have to push them at beginning and pop them at the end): 
*/

# TODO: Figure out if my register usage is good here and that I can use caller-saved registers in what's not a leaf function (though I push and pop them beforehand, so I should be good)
evaluate: 

    # Save previous function's base pointer and update this one's to the bottom of the stack 
    pushq %rbp  
    movq %rsp, %rbp

    # Fill print()'s parameter list before we call it 
    # We have to shift arguments around b/c the call structure for print is a little different than what was passed into this function (1 new, 1->2, 2->3, 3->4)
    # We have to essentially fill our arguments backwards because otherwise we overwrite stuff
    movq %rdx, %rcx # Fourth argument is the upper bound, which is our original third argument
    movq %rsi, %rdx # Third argument is the lower bound, which is our original second argument
    movq %rdi, %rsi # Second argument is the actual string from the struct, which is the same address as the struct itself 
    movq $.LC0, %rdi # First argument is the print-formatted string, which we can just copy from read-only memory 

    # Our parameters, being caller-saved parameters, have no guarantee that they will be the same after a call to print(). 
    # So, we push these onto the stack before our call (and will pop them back off afterwards). 
    pushq %rsi # Push the pointer to the struct onto the stack 
    pushq %rdx # Push the lower bound onto the stack 
    pushq %rcx # Push the upper bound onto the stack 
    xorq %rax, %rax # Need to zero out the return value before calls 

    # Calling print for the first time 
    call print 

    # Popping our three parameters back off of the stack (in reverse order b/c stack is LIFO)
    # Popping back into the registers that they need to be for the count call, NOT what we pushed them as 
    popq %rdx # We pushed the upper bound as rcx (4th param), we pop it into rdx (3rd param)
    popq %rsi # We pushed the lower bound as rdx (3rd param), we pop it into rsi (2nd param)
    popq %rdi # We pushed the address of our struct as rsi (2nd param), we pop it into rdi (1st param) 

    # Pushing our parameters back onto the stack (as is our duty by using caller-saved registers)
    pushq %rdi 
    pushq %rsi 
    pushq %rdx 

    # Calling count() 
    # count() has the same parameter set, so we don't need to move around our three parameter arguments at all 
    # This fills %rax with the correct value, we don't need to do something like %rax = count() because we're too cool for C
    call count

    # Popping our three parameters back off the stack, restoring their values regardless of what happened inside count()  
    popq %rdx 
    popq %rsi 
    popq %rdi 
    
    # Fill print()'s parameters list before we call it 
    # Essentially the same as the first print() call, but the second argument is now the return argument instead of struct name or w/e 
    movq %rdx, %rcx # Fourth argument is the upper bound, which is our original third argument
    movq %rsi, %rdx # Third argument is the lower bound, which is our original second argument
    movq %rax, %rsi # Second argument is the RETURN VALUE that count returned
    movq $.LC1, %rdi # First argument is the print-formatted string, which we can just copy from read-only memory 

    # We need to save whatever count() put in rax() through this call! 
    pushq %rax 

    # rax needs zeroed out before function calls
    xorq %rax, %rax 

    # Note: No need to preserve our argument values (i.e. push/pop them); We don't need them after this call, so we don't care if we still have access to the values afterward 

    # Calling print for the second time 
    call print 

    # Restoring the push we did right beforehand
    pop %rax 

    # Restore stack frame of function this function was callee of 
    movq %rbp, %rsp 
    popq %rbp 

    # Transfer control back to caller function 
    ret

    # Assembler directive that essentially means "mark off this amount of space for this function"
    .size evaluate, .-evaluate
