/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.68781
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280

/* Function definitions, graphics library */
#include "libatc.h"
#include "p1.h"
#include <math.h> 
#include <stdio.h> /* TODO: Remove this in final product, just here for debug */

/* Runs the program, erroring out in the case of import or libatc initialization issues */
int main() {    
    
    int initValue = al_initialize();
    if (initValue != 0) {
        execSimulation();
    } else {
        printf("Initialization Error! Error Code %d\n", initValue);
    }
}

void displayInput() {

    char planeName[15]; 
    int xPos, yPos, altitude; 
    short xPosMiles, yPosMiles, flightLevel, airspeed, heading;

    int input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading);
    while (input != EOF) {

        flightLevel = getFlightLevelFromFeet(altitude);
        xPosMiles = xPos * (1.0 / FEET_PER_MILE);
        yPosMiles = yPos * (1.0 / FEET_PER_MILE);

        drawPlane(planeName, xPosMiles, yPosMiles, flightLevel, airspeed, heading); 
        input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading); 
    }

    al_refresh();
    /* To make this hang, use getchar() (though I can't get that to work) or a sleep(seconds) statement here */
    al_teardown();
}

/* Runs the simulation itself, loading in data then displaying it. Assumes libatc is working, which is checked in main (which calls this). */
void execSimulation() {
    short time = 0;
    short frameNumber = 1; 
    while (time < 10) {
        execFrame(time); 
        sleep(1); 
        time++;
    }
}

/* Updates the frame with exactly 1 second's worth of action */
void execFrame(short time) {
    al_clear();
    al_clock(time);
    al_plane(40, 9, "Blackbird", 455, 2200, 45);
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
    return (x >= 0 && x <= (COLORADO_WIDTH_MILES * FEET_PER_MILE)) && (y >= 0 && y <= (COLORADO_HEIGHT_MILES * FEET_PER_MILE));  
}

/* Converts passed-in feet amount to *horizontal* grid units */
short xToGrid(int x) {
    return ((float) x / FEET_PER_MILE) * (al_max_X() - al_min_X()) / COLORADO_WIDTH_MILES;
}

/* Converts passed-in feet amount to *vertical* grid units */
short yToGrid(int y) {
    return ((float) y / FEET_PER_MILE) * (al_max_Y() - al_min_Y()) / COLORADO_HEIGHT_MILES;
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
