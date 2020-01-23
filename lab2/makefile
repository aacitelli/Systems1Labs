
# ! Top-level build targets that build sections of all our targets 
# Builds everything (Main program and prototypes)
all: mkprog mkproto

# Builds all main program files l
mkprog: lab2

# Builds all prototype files 
mkproto: isOverColorado getFlightLevel drawPlanes

# ! Main program executables 
# Make p1 executable whenever the p1.o file updates 
lab2: lab2.o libatc.h
	gcc lab2.o -o lab2 -L. -latc -lncurses -lm 

# Recompile whenever my source code is changed 
lab2.o: lab2.c libatc.h 
	gcc -c lab2.c -ansi -pedantic

# ! Prototypes 
# Compile isOverLevel object code to executable  
isOverColorado: isOverColorado.o
	gcc isOverColorado.o -o isOverColorado

# Compile isOverColorado source code to object code 
isOverColorado.o: isOverColorado.c
	gcc -c isOverColorado.c -ansi -pedantic

# Compile getFlightLevel object code to executable 
getFlightLevel: getFlightLevel.o 
	gcc getFlightLevel.o -o getFlightLevel 

# Compile getFlightLevel source code to object code 
getFlightLevel.o: getFlightLevel.c 
	gcc -c getFlightLevel.c -ansi -pedantic 

# Compile drawPlanes object code to executable 
drawPlanes: drawPlanes.o 
	gcc drawPlanes.o -o drawPlanes -L. -latc -lncurses -lm 

# Compile getFlightLevel source code to object code 
drawPlanes.o: drawPlanes.c 
	gcc -c drawPlanes.c -ansi -pedantic 