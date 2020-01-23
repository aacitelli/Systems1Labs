/* Function definitions, graphics library */
#include "libatc.h"
#include <stdio.h>

void exec_program(); 
void drawPlane(); 

/* Runs the program */
int main() {
    int initValue = al_initialize();
    if (initValue != 0) {
        exec_program();
    } else {
        printf("Initialization Error! Error Code %d\n", initValue);
        return -1;
    }    
    return 0;
}

/* Calls all routines that draw the planes, then waits for user input */
void exec_program() {  

    int gridX = al_min_X() + 2, gridY = al_min_Y() + 2; 
    char callsign[15] = "A";
    short flightLevel = 360, knots = 1000, heading = 305; 
    
    short time = 0; 
    while (time < 60 * 60) {
        al_clear();

        time += 60; 
    }

    al_clock(0);
    drawPlane(); 
    al_refresh();

    getchar();
    al_teardown();
}

/* Draws top left plane */
void drawPlane() {
    int gridX = al_min_X() + 2, gridY = al_min_Y() + 2; 
    char callsign[15] = "A";
    short flightLevel = 360, knots = 1000, heading = 305; 
    al_plane(gridX, gridY, callsign, flightLevel, knots, heading);
}


