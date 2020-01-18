# Make p1 executable whenever the p1.o file updates 
p1: p1.o libatc.h
	gcc -o p1 p1.o -L. -latc -lncurses -lm 

# Recompile whenever my source code is changed 
p1.o: p1.c libatc.h 
	gcc -ansi -pedantic -c p1.c 
