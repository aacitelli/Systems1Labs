/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.68781
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define CHANGE_IN_TIME 60 

/* Function definitions, graphics library */
#include "libatc.h"
#include "lab2.h"
#include <math.h> 
#include <stdio.h> /* TODO: Remove this in final product, just here for debug */

/* Runs the program, erroring out in the case of import or libatc initialization issues */
int main() {    
    
    

    /* Testing feet -> grid units conversion */
    printf("X Bounds: (%d, %d)\n", al_min_X(), al_max_X()); 
    printf("Y Bounds: (%d, %d)\n", al_min_Y(), al_max_Y());
    printf("0 Feet to X Grid: %hd\n", xToGrid(0));
    printf("0 Feet to y Grid: %hd\n", yToGrid(0));
    printf("(2006400 - 1) Feet to X Grid: %hd\n", xToGrid(2006399));
    printf("(1478400 - 1) Feet to X Grid: %hd\n", yToGrid(1478399));

    /* Testing drawPlane */
    
    /*
    int initValue = al_initialize();
    if (initValue != 0) {
        execSimulation();
    } else {
        printf("Initialization Error! Error Code %d\n", initValue);
    } */
    return 0;
}

/* Runs the simulation itself, loading in data then displaying it. Assumes libatc is working, which is checked in main (which calls this). */
void execSimulation() {
    short time = 0, frameNumber = 1;
    al_clear();
    startPlanes();   

    /* TODO: Change position check to end program when all planes leave picture */
    while (time < (60 * 10)) {
        sleep(1); 
        time++;
        al_clock(time * CHANGE_IN_TIME);
        al_refresh();
    }
    al_teardown();
}

void startPlanes() {
    char planeName[15]; 
    int xPos, yPos, altitude; 
    short xPosMiles, yPosMiles, flightLevel, airspeed, heading;

    int input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading);
    while (input != EOF) {

        flightLevel = getFlightLevelFromFeet(altitude);

        fprintf(stderr, "Plane Name: %s\n", planeName); 
        fprintf(stderr, "xPos (Feet): %d\n", xPos); 
        fprintf(stderr, "yPos (Feet): %d\n", yPos);
        fprintf(stderr, "Flight Level: %d\n", flightLevel);
        fprintf(stderr, "Airspeed (Knots): %hd\n", airspeed);
        fprintf(stderr, "Heading (Degrees): %hd\n", heading);

        drawPlane(planeName, xPos, yPos, flightLevel, airspeed, heading); 
        input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading); 
    }
    al_refresh();
}

/* Calculates the new x pos based on old position, the current 
    angle, and how much time has passed */
int calcNewX(int oldX, short currAngle, short planeSpeedKnots, float dt) {
    return oldX + (planeSpeedKnots * FEET_PER_KNOT) * cos(currAngle) * dt;
}

/* Calculates the new y pos based on old position, the current 
    angle, and how much time has passed */
int calcNewY(int oldY, short currAngle, short planeSpeedKnots, float dt) {
    return oldY + (planeSpeedKnots * FEET_PER_KNOT) * sin(currAngle) * dt;
}

/* Returns the flight level given a feet amount */
int getFlightLevelFromFeet(int feet) {
    if (feet % 500 < 250) {
        return (feet - (feet % 500)) / 500; 
    } else {
        return (feet + (500 - feet % 500)) / 500;
    }
}

/* Reports whether fed-in x,y coordinates (in feet) are in colorado */
int isOverColorado(int x, int y) {
    return (x >= 0 && x < (COLORADO_WIDTH_MILES * FEET_PER_MILE)) && (y >= 0 && y < (COLORADO_HEIGHT_MILES * FEET_PER_MILE));  
}

/* Converts passed-in feet amount to *horizontal* grid units */
short xToGrid(int x) {
    int gridWidth = al_max_X() - al_min_X();
    return 1 + ((float) x / FEET_PER_MILE / COLORADO_HEIGHT_MILES * gridWidth);
}

/* Converts passed-in feet amount to *vertical* grid units */
short yToGrid(int y) {
    int gridHeight = al_max_Y() - al_min_Y();
    return 1 + ((float) y / FEET_PER_MILE / COLORADO_HEIGHT_MILES * gridHeight);
}

/* Draws a plane with the given parameters */
void drawPlane(char planeName[], int x, int y, 
    short flightLevel, short airspeed, short heading) {   

    /* By personal convention, all passed values are in feet */
    int xGrid = xToGrid(x); 
    int yGrid = yToGrid(y); 

    /* Actually call atc method */
    al_plane(xGrid, yGrid, planeName, flightLevel, airspeed, heading);
}
