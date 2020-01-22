# Make p1 executable whenever the p1.o file updates 
lab2: lab2.o libatc.h
	gcc -o lab2 lab2.o -L. -latc -lncurses -lm 

# Recompile whenever my source code is changed 
lab2.o: lab2.c libatc.h 
	gcc -ansi -pedantic -c lab2.c 
