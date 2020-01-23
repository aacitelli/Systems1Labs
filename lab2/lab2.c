/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.68781
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_WIDTH_FEET (COLORADO_WIDTH_MILES * FEET_PER_MILE)
#define COLORADO_HEIGHT_FEET (COLORADO_HEIGHT_MILES * FEET_PER_MILE)
#define CHANGE_IN_TIME 60 

/* Function definitions, graphics library */
#include "libatc.h"
#include "lab2.h"
#include <math.h> 
#include <stdio.h> /* TODO: Remove this in final product, just here for debug */

/* Runs the program, erroring out in the case of import or libatc initialization issues */
int main() {   
    int initValue = al_initialize();
    if (initValue != 0) {
        atcStartup();
        al_clear();    
        inputLoop();
    } else {
        fprintf(stderr, "Initialization Error! Error Code %d\n", initValue);
    }  
    atcTeardown();
    return 0;
}

/* Loads in data from stdin, sending each plane into the simulation loop sequentially */
void inputLoop() {
    int input; 
    char planeName[15]; 
    int xPos, yPos, altitude; 
    short xPosMiles, yPosMiles, flightLevel, airspeed, heading;
    input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading);
    while (input != EOF) {
        flightLevel = getFlightLevelFromFeet(altitude);
        timerLoop(planeName, xPos, yPos, flightLevel, airspeed, heading); 
        input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading); 
    }
}

/* Goes through the simulation for exactly one plane */
void timerLoop(char planeName[], int x, int y, short fL, short airspeed, short heading) {
    short time = 0; 
    while (isOverColorado(x, y)) {
        al_clear();
        drawPlane(planeName, x, y, fL, airspeed, heading);
        al_refresh();
        al_clock(time++ * CHANGE_IN_TIME);
        sleep(1);
        x = calcNewX(x, heading, airspeed, CHANGE_IN_TIME);
        y = calcNewY(y, heading, airspeed, CHANGE_IN_TIME);
    }
}

/* Runs any functions used during libatc startup */
void atcStartup() {
    al_clear();
}

/* Runs any functions used during libatc shutdown */
void atcTeardown() {
    al_teardown();
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

/* Converts passed-in feet amount to *horizontal* grid units */
short xToGrid(int x) {
    short minX = al_min_X(), maxX = al_max_X();
    short gridWidth = maxX - minX;
    return lround(minX + ((float) x * (1.0 / COLORADO_WIDTH_FEET) * (gridWidth / 1.0))); 
}

/* Converts passed-in feet amount to *vertical* grid units */
short yToGrid(int y) {
    short minY = al_min_Y(), maxY = al_max_Y();
    short gridHeight = maxY - minY;
    return lround(minY + ((float) y * (1.0 / COLORADO_HEIGHT_FEET) * (gridHeight / 1.0)));
}

/* Draws a plane with the given parameters. Assumes passed-in x,y are in feet. */
void drawPlane(char planeName[], int x, int y, 
    short fL, short airspeed, short heading) {   
    int xGrid = xToGrid(x); 
    int yGrid = yToGrid(y); 
    al_plane(xGrid, yGrid, planeName, fL, airspeed, heading);
}

/* Returns the flight level given a feet amount */
int getFlightLevelFromFeet(int feet) {
    if (feet % 500 < 250) {
        return (feet - (feet % 500)) / 100; 
    } else {
        return (feet + (500 - feet % 500)) / 100;
    }
}

/* Reports whether fed-in x,y coordinates (in feet) are in colorado */
int isOverColorado(int x, int y) {
    return (x >= 0 && x < (COLORADO_WIDTH_MILES * FEET_PER_MILE)) && (y >= 0 && y < (COLORADO_HEIGHT_MILES * FEET_PER_MILE));  
}
