/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.687809855643
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_WIDTH_FEET (COLORADO_WIDTH_MILES * FEET_PER_MILE)
#define COLORADO_HEIGHT_FEET (COLORADO_HEIGHT_MILES * FEET_PER_MILE)
#define CHANGE_IN_TIME 60 

/* Function definitions, graphics library */
#include "libatc.h"
#include "lab2.h"
#include <math.h> 
#include <stdio.h>

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
    FILE *fp = fopen("planes.output", "w");
    int input; 
    char planeName[15]; 
    int xPos, yPos, altitude; 
    short xPosMiles, yPosMiles, airspeed, heading;
    input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading);
    while (input != EOF) {
        airspeed = airspeed * FEET_PER_KNOT; /* Convert knots -> feet */
        printHeaderInformation(fp);
        timerLoop(planeName, xPos, yPos, altitude, airspeed, heading, fp); 
        fprintf(fp, "\n");
        input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading); 
    }
}

/* Goes through the simulation for exactly one plane */
void timerLoop(char planeName[], int x, int y, int altitude, short airspeed, short heading, FILE *output) {
    short time = 0; 
    while (isOverColorado(x, y)) {
        al_clear();        
        drawPlane(planeName, x, y, altitude, airspeed, heading);
        al_refresh();
        output(time, planeName, x, y, altitude, airspeed, heading, output);
        al_clock((time++) * CHANGE_IN_TIME);        
        sleep(1);
        x = calcNewX(x, heading, airspeed, CHANGE_IN_TIME);
        y = calcNewY(y, heading, airspeed, CHANGE_IN_TIME);
    }
}

/* Outputs the information for a given frame */
void output(short time, char planeName[], int x, int y, int altitude, short airspeed, short heading, FILE *output) {
    fprintf(output, "%3hds ", (time * CHANGE_IN_TIME)); 
    fprintf(output, "%14s ", planeName);
    fprintf(output, "(%7d, %7d) ", x, y);
    fprintf(output, "(%3hd, %3hd) ", xToGrid(x), yToGrid(y));
    fprintf(output, "%5dft ", altitude);
    fprintf(output, "FL%3hd ", getFlightLevelFromFeet(altitude));
    fprintf(output, "%4hdK ", lround((float) airspeed / FEET_PER_KNOT));
    fprintf(output, "H%3hd\n", heading);
}

/* Prints the header information that comes at the beginning of every plane's output */
void printHeaderInformation(FILE *output) {
    fprintf(output, " ET  ");
    fprintf(output, "   Callsign    ");
    fprintf(output, "(      x,       y) ");
    fprintf(output, "( gx,  gy) ");
    fprintf(output, "  Alt   ");
    fprintf(output, "FL    ");
    fprintf(output, "Knots ");
    fprintf(output, " Deg\n");
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
int calcNewX(int oldX, short currAngle, short planeSpeedFeet, float dt) {
    return oldX + planeSpeedFeet * cos(degToRad(convertAngle(currAngle))) * dt;
}

/* Calculates the new y pos based on old position, the current 
    angle, and how much time has passed */
int calcNewY(int oldY, short currAngle, short planeSpeedFeet, float dt) {
    return oldY + planeSpeedFeet * sin(degToRad(convertAngle(currAngle))) * dt;
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
    return (1 + maxY) - lround(minY + ((float) y * (1.0 / COLORADO_HEIGHT_FEET) * (gridHeight / 1.0)));
}

/* Draws a plane with the given parameters. Assumes passed-in x,y are in feet. */
void drawPlane(char planeName[], int x, int y, 
    short altitude, short airspeed, short heading) {   
    int xGrid = xToGrid(x); 
    int yGrid = yToGrid(y); 
    short fL = getFlightLevelFromFeet(altitude);
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

/* Converts angle in our rotational system to unit circle */
int convertAngle(int degrees) {
    int result = 90 - degrees;
    if (result < 0) {
        result = 360 + result;
    }
    return result;
}

/* Converts degrees to radians */
float degToRad(int degrees) {
    return degrees * (M_PI / 180); 
}