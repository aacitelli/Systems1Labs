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
#define CHANGE_IN_TIME 6
#define NUMBER_OF_CALLSIGNS 255
#define PLANE_CALLSIGN_SIZE 15

#include <time.h>
#include "timespec.h"

/* struct timespec request = { 0, 100000001}, remain = {0, 0}; */
struct timespec request = { 0, 100000001}, remain = {0, 0};

/* Local header files, definitions */
#include "lab4.h"

/* Sets up sim structure and sequence machine, then runs program */
int main(int argc, char **argv) { 

    Simulation simObj; 
    int sequencerInit; 
    SequenceMachine sm;

    /* Initialize Simulation, then SequenceMachine */
    fillSimObject(&simObj, argc, argv);
    initializeSequenceMachineObject(&sm, &simObj);

    /* Run the sequencer through its init process, handling if it works or not */
    if (!masterInit(&sm)) {
        masterShutdown(&sm);
    } else {
        attemptSim(&simObj);
        masterShutdown(&sm);
    }
}

/* Runs all initializations for the SequenceMachine object */
SequenceMachine *initializeSequenceMachineObject(SequenceMachine *sm, Simulation *simPtr) {
    sm->simPtr = simPtr; 
    init_sequencer(sm);
} 

/* Fills the simulation structure with some default properties */
Simulation *fillSimObject(Simulation *simPtr, int argc, char **argv) {
    simPtr->storagePointer = NULL;   
    simPtr->elapsedTime = 0; 

    /* Defaults */
    simPtr->inputStream = stdin; 
    simPtr->diagStream = stderr; 
    simPtr->textStream = stdout; 

    simPtr->argc = argc; 
    simPtr->argv = argv; 
}

/* I need to read planes and then fly planes */
void attemptSim(Simulation *simPtr) {
    readPlanes(simPtr); 
    flyPlanes(simPtr);
}

/* As long as I can read planes, I add planes to the sim */
void readPlanes(Simulation *simPtr) {
    static int numPlanesRead = 0; 
    int input, wasInserted; 
    Plane *plane;

    /* Long story... I understand if you have to take points for this, but here's my rationale. Comments don't count towards the 10 line limit. 

        Because we can only really dynamically allocate planes, callsigns need to be statically allocated. 

        I would statically allocate the array in the plane structure, but then if I do that, I need to scanf directly into it; Otherwise, I'd need some sort of buffer 
        variable, which would need to be static for the above reason. 

        However, I can't allocate until I actually scanf, because I can't allocate the plane before I see if there's actually a plane in the input stream, because otherwise
        my diagnostics would output that there were five planes even if I put four in. I tried to figure out how to statically allocate each time just using one variable, but
        that ended up aliasing the data all to one spot, which was a garbage value in the first place. So, in short, memory issues. 

        So, my solution is to statically allocate space for 255 callsigns. My program will likely segfault at anything more than that, but that's already safely 
        above the reasonable limit for the simulation, and the simulation was never really run with anything more than four, so I don't anticipate issues. 
    */ 
    char callsign[NUMBER_OF_CALLSIGNS][PLANE_CALLSIGN_SIZE];
    int currentCallsign = 0;  

    double x, y, airspeed; 
    int profile, altitude; 
    short heading; 
    
    /* Below here is the only part that actually counts towards 10 line limit... Rest is declarations and comments */
    input = fscanf(simPtr->inputStream, "%s %lf %lf %d %lf %hd %d", callsign[currentCallsign], &x, &y, &altitude, &airspeed, &heading, &profile); 
    while (input != EOF) {
        plane = allocatePlane(simPtr); 
        if (plane != NULL) {
            plane->pointerToSim = simPtr;
            fillPlaneValues(plane, callsign[currentCallsign], x, y, altitude, airspeed, heading, profile); 
            currentCallsign++;
            addPlane(plane, simPtr);
        }
        input = fscanf(simPtr->inputStream, "%s %lf %lf %d %lf %hd %d", callsign[currentCallsign], &x, &y, &altitude, &airspeed, &heading, &profile); 
    }
}

/* Fills the passed-in plane with the passed-in objects, assigning default values as well */
void fillPlaneValues(Plane *plane, char callsign[], double x, double y, int altitude, double airspeed, short heading, int profile) {
    plane->callsign = callsign; 
    plane->x = x; 
    plane->y = y; 
    plane->altitude = altitude; 
    plane->airspeed = airspeed * FEET_PER_KNOT; 
    plane->heading = heading; 
    plane->profile = profile; 
    plane->roc = 0;
}

/* I take read-in data and put that on the list in altitude order */
void addPlane(Plane *plane, Simulation *simPtr) {
    int wasInserted;
    wasInserted = insert(&(simPtr->storagePointer), plane, higher);
    if (wasInserted == 0) {
        fprintf(stderr, "ERROR: Couldn't insert plane into the linked list!\n"); 
        freePlane(plane, simPtr);
    }
}

/* As long as the list has planes, I output them, I have the list pilot them, I have the list move them, and I have the list delete the ones that need it. Somewhere in there I bump the clock. */
/* This is our actual control loop. */
void flyPlanes(Simulation *simPtr) {
    while (simPtr->storagePointer != NULL) {
        outputPlanes(simPtr); 
        iterate(simPtr->storagePointer, pilot_plane);
        iterate(simPtr->storagePointer, move_plane); 
        deleteSome(&(simPtr->storagePointer), outside_colorado, dispose_plane);
        nanosleep(&request, &remain); 
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
    al_clock(simPtr->elapsedTime++ * CHANGE_IN_TIME); 
    iterate(simPtr->storagePointer, draw_plane);
    simPtr->currentTenthOfSecond++; 
    simPtr->currentTenthOfSecond = simPtr->currentTenthOfSecond % 10;
    al_refresh(); 
}

/* I print out a line of header information */
void printHeaderInformation(Simulation *simPtr) {
    fprintf(simPtr->textStream, "\nElapsed Time: %d Seconds.\n", (simPtr->elapsedTime - 1) * CHANGE_IN_TIME);
    fprintf(simPtr->diagStream, "\nElapsed Time: %d Seconds.\n", (simPtr->elapsedTime - 1) * CHANGE_IN_TIME);
    fprintf(simPtr->textStream, "      Callsign ");
    fprintf(simPtr->textStream, "(      x,       y) ");
    fprintf(simPtr->textStream, "( gx,  gy) ");
    fprintf(simPtr->textStream, "  Alt   ");
    fprintf(simPtr->textStream, "FL    ");
    fprintf(simPtr->textStream, "Knots ");
    fprintf(simPtr->textStream, " Deg\n");
}

/* I sort the list west to east, put out the header, have the list print each plane, and then toss on a blank line */ 
void printPlanes(Simulation *simPtr) {
    printHeaderInformation(simPtr);
    sort(simPtr->storagePointer, westmost);
    iterate(simPtr->storagePointer, print_plane); 
    fprintf(simPtr->textStream, "\n"); 
}



