
# ! Top-level build targets that build sections of all our targets 
# Builds everything (Main program and prototypes)
all: mkprog mkproto

# Builds all main program files l
mkprog: lab2

# Builds all prototype files 
mkproto: isOverColorado

# ! Main program executables 
# Make p1 executable whenever the p1.o file updates 
lab2: lab2.o libatc.h
	gcc lab2.o -o lab2 -L. -latc -lncurses -lm 

# Recompile whenever my source code is changed 
lab2.o: lab2.c libatc.h 
	gcc -c lab2.c -ansi -pedantic

# ! Prototypes 
# isOverColorado Function Testing 
isOverColorado: isOverColorado.o
	gcc isOverColorado.o -o isOverColorado

isOverColorado.o: isOverColorado.c
	gcc -c isOverColorado.c -ansi -pedantic