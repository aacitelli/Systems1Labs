/* Function definitions, graphics library */
#include "libatc.h"
#include <stdio.h>

void exec_program(); 
void drawTopLeftPlane(); 
void drawTopRightPlane(); 
void drawBottomLeftPlane(); 
void drawBottomRightPlane();

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

/* Calls all routines that draw the planes */
void exec_program() {
    drawTopLeftPlane(); 
    drawTopRightPlane();
    drawBottomLeftPlane();
    drawBottomRightPlane();
    al_refresh();
    getchar();
    al_teardown();
}

/* Draws top left plane */
void drawTopLeftPlane() {
    int gridX = al_min_X() + 10, gridY = al_min_Y() + 5; 
    char callsign[15] = "Top Left";
    short flightLevel = 360, knots = 1000, heading = 305; 
    al_plane(gridX, gridY, callsign, flightLevel, knots, heading);
}

/* Draws top right plane */
void drawTopRightPlane() {
    int gridX = al_max_X() - 10, gridY = al_min_Y() + 5; 
    char callsign[15] = "Top Right";
    short flightLevel = 360, knots = 1000, heading = 45; 
    al_plane(gridX, gridY, callsign, flightLevel, knots, heading);
}

/* Draws bottom left plane */
void drawBottomLeftPlane() {
    int gridX = al_min_X() + 10, gridY = al_max_Y() - 5; 
    char callsign[15] = "Bottom Left";
    short flightLevel = 360, knots = 1000, heading = 225; 
    al_plane(gridX, gridY, callsign, flightLevel, knots, heading);
}

/* Draws bottom right plane */
void drawBottomRightPlane() {
    int gridX = al_max_X() - 10, gridY = al_max_Y() - 5; 
    char callsign[15] = "Bottom Right";
    short flightLevel = 360, knots = 1000, heading = 135; 
    al_plane(gridX, gridY, callsign, flightLevel, knots, heading);
}


