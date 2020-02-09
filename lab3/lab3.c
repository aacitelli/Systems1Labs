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
#include "lab3.h"

/* Runs the program, erroring out in the case of import or libatc initialization issues */
int main() {   
    int initValue;
    initValue = al_initialize(); 
    if (initValue != 0) {
        fprintf(stderr, "DEBUG: Correctly initialized graphics!\n");
        attemptSim();
    } else {
        fprintf(stderr, "ERROR: Couldn't initialize graphics! Error Code %d\n", initValue);
    }  
    al_teardown();
    return initValue != 0 ? 0 : -1;
}

/* I need to read planes and then fly planes */
void attemptSim() {
    Simulation *simPtr; 
    fprintf(stderr, "DEBUG: About to malloc Simulation pointer!\n"); /* TODO: Remove */
    simPtr = (Simulation *) malloc(sizeof(Simulation)); 
    if (simPtr == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate space for Simulation structure!\n"); 
        free(simPtr);
    } else {
        fprintf(stderr, "DEBUG: Successfully allocated space for Simulation structure!\n");
    }
    readPlanes(simPtr); 
    flyPlanes(simPtr);
}

/* As long as I can read planes, I add planes to the sim */
void readPlanes(Simulation *simPtr) {
    static int numPlanesRead = 0; 
    int input; 
    char planeName[15]; 
    double x, y, altitude, airspeed; 
    short heading, pilotProfile;
    input = scanf("%s %lf %lf %lf %lf %hd %hd", planeName, &x, &y, &altitude, &airspeed, &heading, &pilotProfile);
    while (input != EOF) {
        
        airspeed = airspeed * FEET_PER_KNOT; /* Convert knots -> feet */

        fprintf(stderr, "--------------------------------------\n");
        fprintf(stderr, "Just read in the following plane:\n");       
        fprintf(stderr, "Name: %s\n", planeName); 
        fprintf(stderr, "(x, y) in Feet: (%lf, %lf)\n", x, y); 
        fprintf(stderr, "Altitude in Feet: %lf\n", altitude); 
        fprintf(stderr, "Airspeed in Knots: %lf\n", airspeed / FEET_PER_KNOT);
        fprintf(stderr, "Airspeed in Feet: %lf\n", airspeed); 
        fprintf(stderr, "Heading: %hd\n", heading); 
        fprintf(stderr, "Flight Profile: %hd\n", pilotProfile); 
        fprintf(stderr, "That was plane #%hd read in.\n", ++numPlanesRead);
        fprintf(stderr, "\n");

        fprintf(stderr, "Calling addPlane with all of that.\n");
        addPlane(planeName, x, y, altitude, airspeed, heading, pilotProfile, simPtr);
        input = scanf("%s %lf %lf %lf %lf %hd %hd", planeName, &x, &y, &altitude, &airspeed, &heading, &pilotProfile); 
    }
}

/* I take read-in data, move it to dynamic memory, and put that on the list in altitude order */
void addPlane(char *planeName, double x, double y, double altitude, double airspeed, short heading, int pilotProfile, Simulation *simPtr) {
    /* Dynamically allocate one plane's worth of memory */
    int wasInserted;
    Plane *plane; 

    fprintf(stderr, "Allocating memory for the plane.\n"); 
    plane = (Plane *) allocatePlane(); 

    /* Take the data we have and put it in the Plane object */
    plane->planeName = planeName; 
    plane->x = x; 
    plane->y = y; 
    plane->altitude = altitude; 
    plane->airspeed = airspeed; 
    plane->heading = heading; 
    plane->profile = pilotProfile; 
    plane->pointerToSim = simPtr; 

    /* If it failed to insert, free the pointer we tried to allocate it to */
    wasInserted = insert(&(simPtr->storagePointer), plane, higher);
    if (wasInserted == 0) {
        fprintf(stderr, "Couldn't insert plane into the linked list!\n"); 
        free(plane);
    } else {
        fprintf(stderr, "Successfully inserted plane into the linked list.\n");
    }
}

/* As long as the list has planes, I output them, I have the list pilot them, I have the list move them, and I have the list delete the ones that need it. Somewhere in there I bump the clock. */
/* This is our actual control loop. */
void flyPlanes(Simulation *simPtr) {
    static int framesRendered = 0; 
    /* When this becomes a null pointer, we know the linked list is empty and we have no planes left */ 
    while (simPtr->storagePointer != NULL) {
        fprintf(stderr, "----------------------------\n");
        fprintf(stderr, "Still planes in the linked list. Doing frame %d\n", ++framesRendered);
        al_clock(simPtr->elapsedTime++ * CHANGE_IN_TIME); 

        /* Do all screen/file output */
        outputPlanes(simPtr); 

        /* Modify direction, altitude, etc. due to pilot changes */ 

        fprintf(stderr, "Having the list move each plane.\n");
        iterate(simPtr->storagePointer, move_plane); 

        fprintf(stderr, "Have the list delete each plane outside of Colorado.\n");
        deleteSome(&(simPtr->storagePointer), &outside_colorado, dispose_plane);

        fprintf(stderr, "Sleeping for 1 second.\n");
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
    fprintf(stderr, "Sorting planes from highest -> lowest altitude.\n");
    sort(simPtr->storagePointer, higher); 
    fprintf(stderr, "Clearing the canvas.\n");
    al_clear();
    fprintf(stderr, "Updating clock to %d\n", simPtr->elapsedTime * CHANGE_IN_TIME);
    al_clock(simPtr->elapsedTime * CHANGE_IN_TIME); 
    fprintf(stderr, "Having the list iterate through and draw each plane.\n");
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
    sort(simPtr->storagePointer, &westmost);
    printHeaderInformation();
    iterate(simPtr->storagePointer, print_plane); 
    fprintf(stderr, "\n"); 
}

/* I look at the pilot profile contained in the plane that the list handed me and call the right function from my array of pointers using the profile as a subscript */ 
/* Changes altitude and heading */
void pilotPlane() {
    
}



