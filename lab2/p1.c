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
        displayInput();
        /* runSimulation(); */
    } else {
        printf("Initialization Error! Error Code %d\n", initValue);
    }
}

void displayInput() {

    /* char arrays need initial size, so unsigned char size should be more than enough */
    char planeName[256]; 
    int xPos, yPos; 
    short xPosMiles, yPosMiles;
    int altitude; 
    short flightLevel; 
    short airspeed; 
    short heading; 

    short counter = 1; 

    /* TODO: Check that the short format specifier is correct */
    int input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading); 
    al_clear();
    al_clock(1000);
    while (input != EOF) {

        fprintf(stderr, "Adding Plane %hd to canvas!\n", counter++); 

        /* TODO: Fix this to round to the nearest 500 or w/e, instead 
            of straight-up dividing by 500 and truncating */
        flightLevel = getFlightLevelFromFeet(altitude);
        xPosMiles = xPos * (1.0 / FEET_PER_MILE);
        yPosMiles = yPos * (1.0 / FEET_PER_MILE);

        /* Debug */
        fprintf(stderr, "Read-in Values: \n"); 
        fprintf(stderr, "Plane Name: %s\n", planeName); 
        fprintf(stderr, "X Position (Feet): %d\n", xPos); 
        fprintf(stderr, "X Position (miles): %hd\n", xPosMiles);
        fprintf(stderr, "Y Position (Feet): %d\n", yPos); 
        fprintf(stderr, "Y Position (miles): %hd\n", yPosMiles);
        fprintf(stderr, "Altitude (FL): %d\n", flightLevel);
        fprintf(stderr, "Airspeed (knots): %hd\n", airspeed); 
        fprintf(stderr, "Heading (degrees): %hd\n", heading);

        drawPlane(planeName, xPosMiles, yPosMiles, flightLevel, airspeed, heading); 
        input = scanf("%s %d %d %d %hd %hd", planeName, &xPos, &yPos, &altitude, &airspeed, &heading); 
    }

    fprintf(stderr, "Read in both planes' data! Exiting while loop.\n");

    fprintf(stderr, "Refreshing atc grid.\n");
    al_refresh();

    fprintf(stderr, "Waiting for char input to proceed.\n");
    getchar();

    sleep(5);

    fprintf(stderr, "Tearing down atc grid.\n");
    al_teardown();
}

/* Runs the simulation itself, calling the necessary libatc functions */
void runSimulation() {
    short time = 0;  
    short frameNumber = 1;   
    while (time < 10) {
        execFrame(time); 
        sleep(1);
        time++;
    }
    al_teardown();
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
/* TODO: Test this, because it's really easy to get wrong */
int calcNewX(int oldX, short currAngle, short planeSpeedKnots, float dt) {
    return oldX + (planeSpeedKnots * FEET_PER_KNOT) * dt * cos(currAngle);
}

/* Calculates the new y pos based on old position, the current 
    angle, and how much time has passed */
/* TODO: Test this, because it's really easy to get wrong */
int calcNewY(int oldY, short currAngle, short planeSpeedKnots, float dt) {
    return oldY + (planeSpeedKnots * FEET_PER_KNOT) * dt * sin(currAngle);
}

/* Returns the flight level given a feet amount */
int getFlightLevelFromFeet(int feet) {
    /* If it needs rounded down, round it down, otherwise round up */
    if (feet % 500 < 250) {
        return (feet - (feet % 500)) / 500; 
    } else {
        return (feet + (500 - feet % 500)) / 500;
    }
}

/* TODO: Figure out if this should return an int or some smaller 
    data type for performance reasons */
/* Based on fed-in X,Y coordinates, reports whether those coordinates
    are inside Colorado */
int isOverColorado(int currX, int currY) {
    if ((currX >= 0 && currX <= (COLORADO_WIDTH_MILES * FEET_PER_MILE)) 
        && currY >= 0 && currY <= (COLORADO_HEIGHT_MILES * FEET_PER_MILE)) {
        return 1;
    }
    return 0;
}

/* Calculates which grid box it should be in, proportional to original miles amount */
short xMilesToGrid(int xPosMiles) {
    int overallGridWidth = al_max_X() - al_min_X(); 
    return (xPosMiles * overallGridWidth) / COLORADO_WIDTH_MILES;
}

short yMilesToGrid(int yPosMiles) {
    int overallGridHeight = al_max_Y() - al_min_Y();
    return (yPosMiles * overallGridHeight) / COLORADO_HEIGHT_MILES;
}

/* Draws a plane with the given parameters */
void drawPlane(char planeName[], int xPosMiles, int yPosMiles, 
    short flightLevel, short airspeed, short heading) {   

    /* Conversion Miles -> Grid Units */ 
    int xGrid = xMilesToGrid(xPosMiles); 
    int yGrid = yMilesToGrid(yPosMiles); 

    /* Actually call atc method */
    al_plane(xGrid, yGrid, planeName, flightLevel, airspeed, heading);
}
