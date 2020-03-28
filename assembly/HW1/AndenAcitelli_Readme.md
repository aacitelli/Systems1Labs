Anden Acitelli, Kirby CSE 2421 10:20am Section 
This the readme file have fun fam 

The value in %rax is 1. 

When I run through with an actual number, I see a ton of numbers. Each register name has an actual hardware address and a number next to it. The top half is all registers and the bottom half is a visual display of the actual assembler code, and the line that we are about to execute. As we can see, gdb stopped right after the "here" label and is about to exec the next line. 

When I run through with "Go Bucks!" I still get the same GUI output, but rax now has the value 0 in it. I presume that this is because the function wasn't able to add 5 and the string correctly, and as 0 is a falsy value, the return value for the entire function was set as false (or 0, in this case, which is equivalent). 