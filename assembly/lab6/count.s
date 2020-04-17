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
.globl count

/* 
    Register Tracking: 
    Parameters: 
    %rdi = Address of Structure 
    %rsi = Lower Bound (Inclusive) 
    %rdx = Upper Bound (Inclusive) 
    %rax (Return Value): Using this to store number between, incrementing as we go

    Free Registers: 
    Fourth Through Sixth Parameters: 
    %rcx (Fourth Parameter): Holds the value of the third element of the struct. I'm putting this in a register bc we compare it every loop. 
    %r8 (Fifth Parameter): Holds the actual value of the current array element (like, the value in memory, not the memory address)
    %r9 (Sixth Parameter):    

    Other Caller-Saved Registers that I may need to use: 
    %r10
    %r11

    If we have to use any callee-saved stuff, just push/pop them correctly. Not a big deal, but shouldn't need to use them in count.
*/
count: 

    # Save previous base pointer and set up new base pointer 
    pushq %rbp  
    movq %rsp, %rbp 

    # Zero out our return value 
    xorq %rax, %rax

    # Grab the third value in the struct 
    # Should be Base Memory of Struct + (21 * 1 Bytes) + (10 * 2 Shorts)
    # Possible off-by-one error here
    # 41 = (21 Bytes * 1 Byte/Byte) + (10 Shorts * 2 Bytes/Short)
    # TODO: Figure out why each of these are off-by-one from what I expect above 

    # Grab the value we want to go up to 
    # 42 is the hardcoded offset to get this value from the struct (entirely based off struct size)
    xorq %rcx, %rcx
    movw 42(%rdi), %cx 

    # Zero out the index of the array that we're gonna grab 
    xorq %rbx, %rbx

    start_loop: 

        # Get the actual current array value that we're looking at and put it in a register
        # Putting it in a register because we have to do two compares to it and I'm not about to do three memory accesses, god forbid
        # 22 is the offset from the base of the struct to the start of the numbers array
        xorq %r8, %r8 # Could probably technically just do this once before the loop
        movw 22(%rdi, %rbx, 2), %r8w
        inc %rbx 

        # Lower bound is a long that's in %rsi
        # Upper bound is a long that's in %rdx 

        # If it's >= the first bound, then cmp(lowerBound, number) will be negative or zero. If the result is nonnegative (~SF), we can check the second one.
        cmpq %rsi, %r8
        jns more_than_or_equal_to_first_bound 
        jmp loop_end # Not inside our bound if the last line didn't jump so it got here, jump to end 

        more_than_or_equal_to_first_bound: 

        # If it's <= the second bound, then cmp(number, upperBound) will be nonnegative (we switch the order relative to the first one)
        cmpq %r8, %rdx
        jns less_than_or_equal_to_second_bound
        jmp loop_end # Not inside our bound if the last line didn't jump so it got here, jump to end 

        less_than_or_equal_to_second_bound: 

            # If it got to here, then it's entirely within our bound and we increment our return value accordingly 
            inc %rax 
            jmp loop_end # Technically redundant, but helps w/ clarity and logical readability 

        loop_end: 

        # TODO: Write condition(s) for returning to start of loop 
        # Jump if our current index is less than the third argument 
        # %rbx is the element INDEX that we're ABOUT to check (in the next iteration of the loop) 
        # %rcx is the element NUMBER that is the last NUMBER we should read. So, %rcx - 1 is the last INDEX we should read. 
        # So, if %rbx - %rcx ISN't negative (but is zero or positive), then the element we just processed was our last. So, we need %rbx - %rcx to be NONNEGATIVE here to get out of the loop. So, we jump if it IS negative. 
        cmpq %rcx, %rbx
        js start_loop 

    break: 

    # Move back to the top of our stack frame and set our stack pointer back up 
    movq %rbp, %rsp 
    popq %rbp 
    ret

    # Assembler directive that means "mark off this amount of space for this function"
    .size count, .-count
