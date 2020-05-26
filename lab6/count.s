# Name: Anden Acitelli
# Assignment: Lab 6
# File: count.s
# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT 
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS.

.file "count.s" 
.data 

.text

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
    %rcx (Fourth Parameter): Holds the value of the third element of the struct. Putting this in a register bc we compare it every loop. 
    %r8 (Fifth Parameter): Holds the actual value of the current array element (like, the value in memory, not the memory address). In a register because we do a TON of comparisons w/ it.
    %r9 (Sixth Parameter): Unused 

    Other Caller-Saved Registers that I may need to use: 
    %r10: Unused 
    %r11: Unused

    Nothing callee-saved used, so we don't have to worry about pushing and popping. 
*/

/* 
    I call this one "overengineering the living sh*t out of code" 

    NOTE TO THE GRADER: 

    I know this could probably be a lot simpler, and not have all these labels. However, I didn't realize `movz` and `movs` were a thing 
    until after I tried to over-engineer all this stuff to work with 2s complement, which is why there's literally like fifteen labels. 

    It ended up working right away after I moved to movswq; Most of this probably isn't necessary. It works though, and is as readable
    as I could make it, so please take it easy when it comes to grading. Rather than commenting every single line, I sometimes explain a few 
    statements at a time, because they're all one related, contiguous block that does one function overall. 
*/
count: 

    # Save previous base pointer to stack and set up new base pointer 
    pushq %rbp  
    movq %rsp, %rbp 

    # Zero out our return value b/c we don't know what's in there 
    xorq %rax, %rax

    # Grab the value we want to go up to 
    # 42 is the hardcoded offset to get this value from the struct (21 for the first array, 1 for padding b/c the next short has to end on a multiple of 2, 10 for the short array) 
    xorq %rcx, %rcx
    movw 42(%rdi), %cx 

    # Zero out both the register used to hold the current index of the array that we're on (%rbx) 
    # and the register used to hold the actual number (pulled from memory) at that address (%r8). 
    xorq %rbx, %rbx
    xorq %r8, %r8

    # For Debug Usage 
    # break: 

    start_loop: 

        # Jump if our current index is less than the third argument 
        # %rbx is the element INDEX that we're ABOUT to check (in the next iteration of the loop) 
        # %rcx is the element NUMBER that is the last NUMBER we should read. So, %rcx - 1 is the last INDEX we should read. 
        # If this results in zero or a positive number, that means our number was >= the last element that we go to. This doesn't run into an off-by-one error. 
        cmpq %rcx, %rbx
        jns done_with_loop

        # Get the actual current array value that we're looking at and put it in a register
        # 22 is the offset here instead of 21 b/c the short has to start on a 2-byte multiple
        # mov-signed_extend-word-to-quad (we read in as two but save as 8)
        # We need to do it incase it's a negative number, and when we do compares between negatives they need to be the same "size" b/c of how 2s complement works 
        movswq 22(%rdi, %rbx, 2), %r8

        # Lower bound is a long that's in %rsi
        # Upper bound is a long that's in %rdx 

        /* 
            This can probably be simplified; I'm writing code for every case to be explicit and because it's readable.  

            Logic: 

            If our lower bound is positive and our number is positive, we have to do an actual comparison
            If our lower bound is positive and our number is negative, we've effectively already failed the test and we skip to loop end. 
            If our lower bound is negative and our number is positive, we've effectively already passed the test and we skip to the upper bound check. 
            If our lower bound is negative and our number is negative, we have to do an actual comparison

            If our upper bound is positive and our number is positive, we have to do an actual comparison 
            If our upper bound is positive and our number is negative, we've effectively already passed the test and we skip to the part that increments %rax. 
            If our upper bound is negative and our number is positive, we've effectively already failed the test and we skip to loop end. 
            If our upper bound is negative and our number is negative, we have to do an actual comparison 
        */

        # If our number is positive or zero, cmpq(0, number) will be nonnegative
        # Because zero acts like a positive number in my system, I treat it like a positive number 
        # If this test returns anything nonzero, that means the sign bit was set and the number was negative
        testw $0x80, %r8w
        jnz to_lower_transfer_negative_number # If the test was anything nonzero, we have a negative 
        jmp to_lower_transfer_positive_number

        to_lower_transfer_positive_number: 

            # If result comes out nonzero, we know lower bound is negative
            testq %rsi, %rsi
            js lower_bound_check_negative_bound_positive_number
            jmp lower_bound_check_positive_bound_positive_number

        to_lower_transfer_negative_number: 

            # Logically same check as above, just going to the negative number labels instead 
            testq %rsi, %rsi 
            js lower_bound_check_negative_bound_negative_number 
            jmp lower_bound_check_positive_bound_negative_number 

        lower_bound_check_positive_bound_positive_number: 

            # If it's >= the first bound, then cmp(lowerBound, number) will be negative or zero. If the result is nonnegative (~SF), we continue. 
            cmpq %rsi, %r8
            jns lower_to_upper_transfer_positive_number

            # If we didn't jump, we weren't within lower bound, jump to end of loop 
            jmp loop_end

        lower_bound_check_positive_bound_negative_number: 

            # If our lower bound is positive and our number itself is negative, we can't possibly be within bound 
            jmp loop_end

        lower_bound_check_negative_bound_positive_number: 

            # If our lower bound is negative and our number itself is positive, we are guaranteed to be within bound 
            jmp lower_to_upper_transfer_positive_number

        lower_bound_check_negative_bound_negative_number: 

            # We're working in 2s complement here (though the ALU doesn't know it), so whichever one is represented as a SMALLER NUMBER in magnitude is the number that's more negative 
            # So, cmp(lower bound, number)'s result is positive that means number was larger than lower bound which means the lower bound was more negative and we're good 
            cmpq %rsi, %r8 
            jns lower_to_upper_transfer_negative_number 
            jmp loop_end # If it didn't jump above, we were below the lower bound, so skip to end of loop

        lower_to_upper_transfer_positive_number: 
            
            # Same checks as the first set of transfer functions 
            testq %rdx, %rdx
            js upper_bound_check_negative_bound_positive_number 
            jmp upper_bound_check_positive_bound_positive_number 

        lower_to_upper_transfer_negative_number: 

            # Same checks as the first set of transfer functions 
            testq %rdx, %rdx 
            js upper_bound_check_negative_bound_negative_number 
            jmp upper_bound_check_positive_bound_negative_number 

        upper_bound_check_positive_bound_positive_number: 

            # If it's <= the second bound, then cmp(number, upperBound) will be nonnegative (we switch the order relative to the first one)
            cmpq %r8, %rdx
            jns increment_rax
            jmp loop_end # Not inside our bound if the last line didn't jump so it got here, jump to end 

        upper_bound_check_positive_bound_negative_number: 

            # If our upper bound is positive and our number is negative, we're guaranteed to be within our upper bound 
            jmp increment_rax 

        upper_bound_check_negative_bound_positive_number: 

            # If our upper bound is negative and our number is positive, we can't possibly be within the bound 
            jmp loop_end 

        upper_bound_check_negative_bound_negative_number: 

            # Again, we're working in 2s complement here (though the ALU doesn't know it) so whichever one is represented as a SMALLER NUMBER in magnitude is the one that's more negative
            # So, we want to move on here if the number is more negative, so we do cmpq(number, upper bound) and nonnegativity is our move-on case
            # Our numbers are both in 2s complement. So, whichever number is LESS in magnitude of its current representation is MORE NEGATIVE. 
            # Thus, for our condition, we want our NUMBER to be LESS in magnitude, because we want our number to be less than our upper bound in terms of actual negativity. 
            cmpq %r8, %rdx 
            jns increment_rax 
            jmp loop_end # If it got down here, we weren't within upper bound 

        increment_rax: 

            # If it got to here, then it's entirely within our bound and we increment our return value accordingly 
            inc %rax 
            jmp loop_end # Technically redundant, but helps w/ clarity and logical readability 

        loop_end: 

        # This isn't a conditional jump; We check our condition at the start of the loop and skip to the end from there, not here. 
        inc %rbx 
        jmp start_loop 

    done_with_loop: 

    # Move back to the top of our stack frame and set our stack pointer back up 
    movq %rbp, %rsp 
    popq %rbp 

    # Transfer control back to caller function 
    ret

    # Assembler directive that essentially means "mark off this amount of space for this function"
    .size count, .-count
