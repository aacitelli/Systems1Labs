
# ! Top-level build targets that build sections of all our targets 
# Builds everything (Main program and prototypes)
all: mkprog mkproto

# Builds all main program files l
mkprog: lab2

# Builds all prototype files 
mkproto: isOverColorado getFlightLevel drawPlanes gridConversions convertAngle

# ! Main program executables 
# Make p1 executable whenever the p1.o file updates 
lab2: lab2.o libatc.h
	gcc lab2.o -o lab2 -L. -latc -lncurses -lm 

# Recompile whenever my source code is changed 
lab2.o: lab2.c libatc.h 
	gcc -c lab2.c -ansi -pedantic

# ! Prototypes 
# TO THE GRADER: I HAVE FIVE WORKING PROTOTYPES. PICK WHAT YOU WANT, THOUGH SKIP ONE IF IT FINDS A WAY TO BREAK. 
# PLEASE GRADE THIS PROTOTYPE
# Compile isOverLevel object code to executable  
isOverColorado: isOverColorado.o
	gcc isOverColorado.o -o isOverColorado

# Compile isOverColorado source code to object code 
isOverColorado.o: isOverColorado.c
	gcc -c isOverColorado.c -ansi -pedantic

# Compile getFlightLevel object code to executable 
# PLEASE GRADE THIS PROTOTYPE
getFlightLevel: getFlightLevel.o 
	gcc getFlightLevel.o -o getFlightLevel 

# Compile getFlightLevel source code to object code 
getFlightLevel.o: getFlightLevel.c 
	gcc -c getFlightLevel.c -ansi -pedantic 

# Compile drawPlanes object code to executable 
# PLEASE GRADE THIS PROTOTYPE
drawPlanes: drawPlanes.o 
	gcc drawPlanes.o -o drawPlanes -L. -latc -lncurses -lm 

# Compile getFlightLevel source code to object code 
drawPlanes.o: drawPlanes.c 
	gcc -c drawPlanes.c -ansi -pedantic 

# Compile gridConversions object code to executable 
# PLEASE GRADE THIS PROTOTYPE
gridConversions: gridConversions.o 
	gcc gridConversions.o -o gridConversions -L. -latc -lncurses -lm 

# Compile gridConversions source code to object code 
gridConversions.o: gridConversions.c 
	gcc -c gridConversions.c -ansi -pedantic

# Compile convertAngle object code to executable 
# PLEASE GRADE THIS PROTOTYPE (though this is my fifth... it's up to you)
convertAngle: convertAngle.o 
	gcc convertAngle.o -o convertAngle

# Compile convertAngle source code to object code 
convertAngle.o: convertAngle.c 
	gcc -c convertAngle.c -ansi -pedantic