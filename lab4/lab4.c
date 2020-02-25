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

#define MICROSECONDS_PER_MILLISECOND 1000 

/* Local header files, definitions */
#include "lab4.h"
#include "altmem.h" 

/* Runs the program, erroring out in the case of import or libatc initialization issues */
int main() {   
    int initValue;
    initValue = al_initialize(); 
    if (initValue != 0) {
        fprintf(stderr, "Drawable area is (%d, %d) to (%d, %d)\n", al_min_X(), al_min_Y(), al_max_X(), al_max_Y());
        attemptSim();
    } else {
        fprintf(stderr, "ERROR: Couldn't initialize graphics! Error Code %d\n", initValue);
    }  
    al_teardown();
    return initValue != 0 ? 0 : -1;
}

/* I need to read planes and then fly planes */
void attemptSim() {
    Simulation simObj;
    simObj.storagePointer = NULL;
    fprintf(stderr, "Calling readPlanes!\n"); 
    readPlanes(&simObj); 
    flyPlanes(&simObj);
}

/* As long as I can read planes, I add planes to the sim */
void readPlanes(Simulation *simPtr) {
    static int numPlanesRead = 0; 
    int input, altitude;  
    char planeName[15]; 
    double x, y, airspeed; 
    short heading, pilotProfile;

    input = scanf("%s %lf %lf %d %lf %hd %hd", planeName, &x, &y, &altitude, &airspeed, &heading, &pilotProfile); 
    while (input != EOF) {
        airspeed = airspeed * FEET_PER_KNOT;
        addPlane(planeName, x, y, altitude, airspeed, heading, pilotProfile, simPtr);
        input = scanf("%s %lf %lf %d %lf %hd %hd", planeName, &x, &y, &altitude, &airspeed, &heading, &pilotProfile); 
    }
}

/* I take read-in data, move it to dynamic memory, and put that on the list in altitude order */
void addPlane(char *planeName, double x, double y, int altitude, double airspeed, short heading, int pilotProfile, Simulation *simPtr) {
    /* Dynamically allocate one plane's worth of memory */
    int wasInserted;
    Plane *plane = (Plane *) allocatePlane(); 
    fillPlaneData(plane, planeName, x, y, airspeed, pilotProfile, altitude, heading, simPtr); 
    wasInserted = insert(&(simPtr->storagePointer), plane, higher);
    if (wasInserted == 0) {
        fprintf(stderr, "ERROR: Couldn't insert plane into the linked list!\n"); 
        free(plane);
    }
}

/* I fill a plane structure with the passed-in data */
void fillPlaneData(Plane *plane, char *planeName, double x, double y, double airspeed, int profile, int altitude, short heading, Simulation *simPtr) {
    plane->planeName = planeName; 
    plane->x = x; 
    plane->y = y; 
    plane->altitude = altitude; 
    plane->airspeed = airspeed; 
    plane->heading = heading; 
    plane->profile = profile; 
    plane->pointerToSim = simPtr;
    plane->roc = 0;  
}

/* As long as the list has planes, I output them, I have the list pilot them, I have the list move them, and I have the list delete the ones that need it. Somewhere in there I bump the clock. */
/* This is our actual control loop. */
void flyPlanes(Simulation *simPtr) {
    static int framesRendered = 0; 
    while (simPtr->storagePointer != NULL) {
        outputPlanes(simPtr); 
        iterate(simPtr->storagePointer, pilot_plane);
        iterate(simPtr->storagePointer, move_plane); 
        deleteSome(&(simPtr->storagePointer), outside_colorado, dispose_plane);
        sleep(1);
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
    al_refresh(); 
}

/* I print out a line of header information */
void printHeaderInformation(Simulation *simPtr) {
    fprintf(stderr, "\nElapsed Time: %d Seconds.\n", (simPtr->elapsedTime - 1) * CHANGE_IN_TIME);
    fprintf(stderr, "      Callsign ");
    fprintf(stderr, "(      x,       y) ");
    fprintf(stderr, "( gx,  gy) ");
    fprintf(stderr, "  Alt   ");
    fprintf(stderr, "FL    ");
    fprintf(stderr, "Knots ");
    fprintf(stderr, " Deg\n");
}

/* I sort the list west to east, put out the header, have the list print each plane, and then toss on a blank line */ 
void printPlanes(Simulation *simPtr) {
    printHeaderInformation(simPtr);
    sort(simPtr->storagePointer, westmost);
    iterate(simPtr->storagePointer, print_plane); 
    fprintf(stderr, "\n"); 
}



