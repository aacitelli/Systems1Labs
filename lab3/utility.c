/* System libraries */ 
#include <math.h>
#include <stdio.h>
#include "structs.h"

/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.687809855643
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_WIDTH_FEET (COLORADO_WIDTH_MILES * FEET_PER_MILE)
#define COLORADO_HEIGHT_FEET (COLORADO_HEIGHT_MILES * FEET_PER_MILE)
#define CHANGE_IN_TIME 60 

/* Converts degrees to radians */
float degToRad(short degrees) {
    return degrees * (M_PI / 180); 
}

/* Converts angle in our rotational system to unit circle */
short convertAngle(short degrees) {
    short result = 90 - degrees;
    if (result < 0) {
        result = 360 + result;
    }
    return result;
}

/* Calculates the new x pos based on old position, the current 
    angle, and how much time has passed */
double calcNewX(double oldX, short currAngle, double planeSpeedFeet) {
    return oldX + planeSpeedFeet * cos(degToRad(convertAngle(currAngle))) * CHANGE_IN_TIME;
}

/* Calculates the new y pos based on old position, the current 
    angle, and how much time has passed */
double calcNewY(double oldY, short currAngle, double planeSpeedFeet) {
    return oldY + planeSpeedFeet * sin(degToRad(convertAngle(currAngle))) * CHANGE_IN_TIME;
}

/* Converts passed-in feet amount to *horizontal* grid units */
short xToGrid(double x) {
    short minX = al_min_X(), maxX = al_max_X();
    short gridWidth = maxX - minX;
    short returnVal = lround(minX + (x * (1.0 / COLORADO_WIDTH_FEET) * (gridWidth / 1.0))); 
    return lround(minX + (x * (1.0 / COLORADO_WIDTH_FEET) * (gridWidth / 1.0))); 
}

/* Converts passed-in feet amount to *vertical* grid units */
short yToGrid(double y) {
    short minY = al_min_Y(), maxY = al_max_Y();
    short gridHeight = maxY - minY;
    short returnVal = (1 + maxY) - lround(minY + (y * (1.0 / COLORADO_HEIGHT_FEET) * (gridHeight / 1.0)));
    return (1 + maxY) - lround(minY + (y * (1.0 / COLORADO_HEIGHT_FEET) * (gridHeight / 1.0)));
}

/* Returns the flight level given a feet amount */
short getFlightLevelFromFeet(int feet) {
    if (feet % 500 < 250) {
        return (feet - (feet % 500)) / 100; 
    } else {
        return (feet + (500 - feet % 500)) / 100;
    }
}

/* Outputs the contents of a plane structure (solely for debug) */
void outputPlaneContents(Plane *plane) {
    fprintf(stderr, "------------------------------\n");
    fprintf(stderr, "outputPlaneContents: \n");
    fprintf(stderr, "Name: %s\n", plane->planeName);  
    fprintf(stderr, "(x,y): (%lf, %lf)\n", plane->x, plane->y); 
    fprintf(stderr, "Airspeed (feet): %lf\n", plane->airspeed); 
    fprintf(stderr, "Flight Profile: %d\n", plane->profile);
    fprintf(stderr, "Altitude (feet): %d\n", plane->altitude); 
}