/* Lab By Anden Acitelli.2 */
/* This lab simulates a plane's path over Colorado, doing all the calculations
    to graphically plot its path in real time. */

/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.687809855643
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_WIDTH_FEET (COLORADO_WIDTH_MILES * FEET_PER_MILE)
#define COLORADO_HEIGHT_FEET (COLORADO_HEIGHT_MILES * FEET_PER_MILE)
#define CHANGE_IN_TIME 60 

/* Local header files, definitions */
#include "planesMemory.c"
#include "functionPointers.c"
#include "libatc.h"
#include "lab3.h"
#include "linkedlist.h"

/* System libraries */
#include <math.h> 
#include <stdio.h>

/* Runs the program, erroring out in the case of import or libatc initialization issues */
int main() {   
    int initValue = al_initialize();
    if (initValue != 0) {
        attemptSim();
    } else {
        fprintf(stderr, "Initialization Error! Error Code %d\n", initValue);
    }  
    atcTeardown();
    char returnValue = initValue != 0 ? 0 : 1;
    return returnValue;
}

/* I need to read planes and then fly planes */
void attemptSim() {
    Simulation *simStruct = malloc(sizeof(Simulation)); 
    if (simStruct == NULL) {
        fprintf(stderr, "Failed to allocate space for Simulation structure!\n"); 
    }
    readPlanes(simStruct); 
    flyPlanes(simStruct);
}

/* As long as I can read planes, I add planes to the sim */
void readPlanes(simStruct) {
    int input, pilotProfile; 
    char planeName[15]; 
    double airspeed, x, y, altitude; 
    short heading;
    input = scanf("%s %e %e %e %e %hd %c", planeName, &x, &y, &altitude, &airspeed, &heading, &pilotProfile);
    while (input != EOF) {
        airspeed = airspeed * FEET_PER_KNOT; /* Convert knots -> feet */
        addPlane(planeName, x, y, altitude, airspeed, heading, pilotProfile, simStruct);
        input = scanf("%s %e %e %e %e %hd", planeName, &x, &y, altitude, &airspeed, &heading, &pilotProfile); 
    }
}

/* I take read-in data, move it to dynamic memory, and put that on the list in altitude order */
void addPlane(char *planeName, double x, double y, double altitude, double airspeed, short heading, int pilotProfile, Simulation *simStruct) {
    /* Dynamically allocate one plane's worth of memory */
    Plane *plane = allocatePlane(); 

    /* Take the data we have and put it in the Plane pointer */
    plane -> planeName = planeName; 
    plane -> x = x; 
    plane -> y = y; 
    plane -> altitude = altitude; 
    plane -> airspeed = airspeed; 
    plane -> heading = heading; 
    plane -> profile = pilotProfile; 

    /* TODO: Put it on the list at the correct altitude */
    int wasInserted = insert(simStruct->storagePointer, plane, higher);
    if (wasInserted == 0) {
        fprintf(stderr, "Couldn't insert plane into the linked list!\n"); 
    }
}

/* As long as the list has planes, I output them, I have the list pilot them, I have the list move them, and I have the list delete the ones that need it. Somewhere in there I bump the clock. */
/* This is our actual control loop. */
void flyPlanes(Simulation *simPtr) {

    /* When this becomes a null pointer, we know the linked list is empty and we have no planes left */ 
    while (simPtr->storagePointer != NULL) {
        outputPlanes(simPtr); 
        pilotPlane
    }
}

/* I draw planes, I print planes and REDACTED */
void outputPlanes(Simulation *simPtr) {
    drawPlanes(simPtr); 
    printPlanes(simPtr);
}

/* I sort the planes by altitude, set up the graphics for one frame, have the list draw each plane, then toss it all on screen for user viewage */
void drawPlanes(Simulation *simPtr) {
    sort(simPtr->storagePointer, higher); 
    al_clear();
    al_clock(simPtr->elapsedTime); 
    iterate(simPtr->storagePointer, draw_plane);
    al_refresh(); 
}

void printHeaderInformation() {
    fprintf(stderr, " ET  ");
    fprintf(stderr, "   Callsign    ");
    fprintf(stderr, "(      x,       y) ");
    fprintf(stderr, "( gx,  gy) ");
    fprintf(stderr, "  Alt   ");
    fprintf(stderr, "FL    ");
    fprintf(stderr, "Knots ");
    fprintf(stderr, " Deg\n");
}

/* I sort the list west to east, put out the header, have the list print each plane, and then toss on a blank line */ 
void printPlanes(Simulation *simPtr) {
    sort(simPtr->storagePointer, westmost);
    printHeaderInformation();
    iterate(simPtr->storagePointer, print_plane); 
    fprintf(stderr, "\n"); 
}

/* I look at the pilot profile contained in the plane that the list handed me and call the right function from my array of pointers using the profile as a subscript */ 
void pilotPlane() {
    
}

/* Update X, Y, Altitude using any helper functions required */
void movePlane() {

}

/* Loads in data from stdin, sending each plane into the simulation loop sequentially */
void inputLoop() {
    
}

/* Converts degrees to radians */
float degToRad(int degrees) {
    return degrees * (M_PI / 180); 
}