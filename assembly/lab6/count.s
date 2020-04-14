# Name: Anden Acitelli
# Assignment: Lab 5
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "count.s" 
.data 

.text

/* 
    Register Tracking: 
    %rdi = First Parameter (Address of Structure)
    %rsi = Second Parameter (Lower Bound, Inclusive)
    %rdx = Third Parameter (Upper Bound, Inclusive)
    %rcx = Fourth Parameter
    %r8 = Fifth Parameter
    %r9 = Sixth Parameter
    %rax = Return Value 
*/

/* 
    Overall Algorithm: 

    - Figure out where in memory I need to go to get to the base of the middle array (store it in a register) 
        - Will need to use another register for the actual index, then use leaq() to get to the actual index in memory. Can use a "moving" register to track 
            the current value. 
        - Think figuring out this memory stuff will be the hard part... how do I deal with a variable length string? 
    - Figure out where in memory I need to go to get to the last value, then smack it in a register 

    1. Figure out memory addresses (think I need three registers to store memory stuff) 
    2. Iterate through the array, looping until the current index is more than the third value 
        - Each iteration, I can do a compare to the low number, then to the high number if it passes the low test
        - If it passes both tests, increment %rax
*/ 
.global count
count: 

    # Save previous base pointer and set up new base pointer 
    pushq %rbp
    movq %rsp, %rbp 

    # Do everything right here

    # Move back to the top of our stack frame and set our stack pointer back up 
    movq %rbp, %rsp 
    popq %rbp 
    ret
