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
    %rcx (Fourth Parameter): 
    %r8 (Fifth Parameter): 
    %r9 (Sixth Parameter): Used Temporarily to Cache First Argument before each print() call 

    Other Caller-Saved Registers that I may need to use: 
    %r10: Used Temporarily to Cache Second Argument before each print() call
    %r11: Used Temporarily to Cache Third Argument before each print() call 

    Callee-Saved Registers Used (just means I have to push them at beginning and pop them at the end): 
*/
evaluate: 

    # Save previous base pointer to stack and set up new base pointer 
    pushq %rbp  
    movq %rsp, %rbp 

    # Move back to the top of our stack frame and set our stack pointer back up 
    movq %rbp, %rsp 
    popq %rbp 

    # Saving all the caller-saved variables that we use in this function to the stack prior to our print call 
    # We only need to save these three because these are the ones we need to pass into count(); We don't care what's in the rest of them. 
    # And if they're needed in the function that called *this one*, they're caller saved, so we're not responsible for that. 
    pushq %rdi
    pushq %rsi 
    pushq %rdx

    # We have to essentially shift the argument list one down for our call to printf; More organized to use other registers to temporarily hold those values 
    # so we don't have to worry about the assignent to one argument overwriting something we need for the next one, as seen below
    # Note: push/pop do not overwrite the values themselves, just throws them on the stack, so we can still read from them here after we do a push 
    movq %rdi, %r9 # Move address of struct to %r9 
    movq %rsi, %r10 # Move lower bound to %r10 
    movq %rdx, %r11 # Move upper bound to %r11 

    # Fill print()'s parameter list before we call it 
    # This one follows the format printf("evaluate: Evaluating '%s' looking for results between %ld and %ld.\n", StringFromStructure, LowerBound, UpperBound)
    # (though, we're using print() which has the same signature as printf, and those arguments are just symbolic names that correspond to the registers below) 
    movq $.LC0, %rdi # First argument is the print-formatted string 
    movq %r9, %rsi # Second argument is the actual string from the struct 
    movq %r10, %rdx # Third argument is the lower bound
    movq %r11, %rcx # Fourth argument is the upper bound 

break: 

    # Calling print for the first time 
    call print 

    # Popping our three parameters back off of the stack (in reverse order b/c stack is LIFO)
    popq %rdx 
    popq %rsi 
    popq %rdi 

    # Have to preserve the values of these regardless across every function call, even count()
    # (although I know count doesn't screw them up because I wrote it, it's convention) 
    pushq %rdi 
    pushq %rsi 
    pushq %rdx 

    # Calling count() 
    # count() has the same parameter set, so we don't need to move around our three parameter arguments at all 
    # This fills %rax with the correct value, we don't need to do something like %rax = count() because we're too cool for C
    call count

    # Popping our three parameters back off the stack 
    popq %rdx 
    popq %rsi 
    popq %rdi 

    # Saving all the caller-saved variables that we use in this function to the stack prior to our print call 
    # I don't think this is *technically* necessary seeing as we don't need to use them after this call, but it's 
    # more maintainable, structured, and readable this way 
    pushq %rdi 
    pushq %rsi 
    pushq %rdx 

    # Again, similarly to above, if we just write our three arguments to their correct arguments to the print call, we end up overwriting stuff. 
    # So, here, I'm caching those values in other (caller-saved) registers. 
    movq %rdi, %r9 # Move address of struct to %r9 
    movq %rsi, %r10 # Move lower bound to %r10 
    movq %rdx, %r11 # Move upper bound to %r11 

    # Fill print()'s parameters list before we call it 
    # This call is in order "evaluate: Found %ld results between %ld and %ld\n"
    movq $.LC1, %rdi # Move formatted string into first argument 
    movq %rax, %rsi # Move return value from count into our second argument 
    movq %r10, %rdx # Move our lower bound into our third argument
    movq %r11, %rcx # Move our upper bound into our fourth argument 

    # Calling print for the second time 
    call print 

    # Popping these back off the stack to save stack space
    # (We don't actually use them again, and we don't need to preserve them for the calling function or anything, but we don't want to keep accruing stack space) 
    popq %rdx 
    popq %rsi 
    popq %rdi 

    # Restore stack frame of function this function was callee of 
    movq %rbp, %rsp 
    popq %rbp 

    # Transfer control back to caller function 
    ret

    # Assembler directive that essentially means "mark off this amount of space for this function"
    .size evaluate, .-evaluate
