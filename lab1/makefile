# Generates test file to test out makefiles 
stuff: makefile 
	date > stuff 
	ls -lt >> stuff 

# Compiles lab1 executable from source file 
lab1: lab1.c 
	gcc -ansi -pedantic -g -o lab1 lab1.c 

# Zips relevant files for project submission
lab1.zip: lab1 lab1.c README_LAB1 makefile
	zip lab1.zip makefile  *.c *.h README_LAB1