# CSE 2421 (Systems 1) Labs

My professor changes up the labs every semester, and code plagiarism is super easy to catch anyway, so I'm pretty sure making this publically available is fine. If you have an issue with it, get in touch at acitelli.2@osu.edu and I'll be happy to take it down. 

## What Is This? 

**If you want good examples of how I write C, look at lab 4. If you want good examples of how I write assembly, look at lab 6.**

This repository contains labs for a class I took covering C and ASM (x86_64, specifically). These are good examples of how I write C and assembly. 

I made this publically available because they're good representations of how I write code, and are proven examples of how I solve problems. I know anyone looking to hire me isn't going to put in the effort for this, but these are all compileable via the makefiles.

TODO: I will probably try and make short gifs of these working or something and paste them in here at some point. 

## What I Learned

Learned the basics of C and x86_64, but here's some notable: 

Misc. Material: 
- **Makefiles**: I became comfortable with makefiles and using them to build C / ASM projects with only one command. 
- **gcc**: Just what we compiled with, nothing special. 
- **Debugging with gdb**: I became *very* good at using gdb to look at registers and variable values to see where my code was performing unexpectedly. 
- **Compiling / Linking**: Learned at a fairly low level how programs are compiled and linked together. 

C Material: 
- **Pointers**: Figured out how they worked. This class would've been a *nightmare* if I didn't understand these well. 
- **Low-Level Memory Management**: I learned how to manually allocate and free memory. 

Assembly Material: 
- **Opcodes**: Learned all the basic opcodes (`mov`, `lea`, `push`, `pop`), etc. 
- **Registers / Calling Conventions**: Learned how to use these, and calling conventions for where I could use which. 
- **Memory Layout**: Learned how size suffixes worked, and how using different memory sizes affects how stuff is laid out in memory. Learned that the stack is a very fun, and confusing place. 
