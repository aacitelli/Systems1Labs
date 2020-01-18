#include "stdio.h"
#include "libatc.h"
#include "p1.h"

/* Runs the program, erroring out in the case of import or libatc initialization issues */
main() {    
    int initValue = al_initialize();
    if (initValue != 0) {
        runSimulation();        
    } else {
        printf("Initialization Error! Error Code %d\n", initValue);
    }
}

/* Runs the simulation itself, calling the necessary libatc functions */
void runSimulation() {
    short time = 0;  
    short frameNumber = 1;   
    while (time < 10) {
        printf("Frame %d\n", frameNumber++);
        execFrame(time); 
        sleep(1);
        time++;
    }
    al_teardown();
}

/* Updates the frame with exactly 1 second's worth of action */
void execFrame(short time) {
    al_clear();
    al_clock(time);
    al_plane(40, 9, "Blackbird", 455, 2200, 45);
    al_refresh();
}