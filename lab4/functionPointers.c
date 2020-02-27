/* System libraries */ 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Our libraries */ 
#include "functionPointers.h"
#include "utility.h"

/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.687809855643
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_WIDTH_FEET (COLORADO_WIDTH_MILES * FEET_PER_MILE)
#define COLORADO_HEIGHT_FEET (COLORADO_HEIGHT_MILES * FEET_PER_MILE)
#define CHANGE_IN_TIME 60

/* Comparison Functions */ 
/* I figure out which of two passed-in planes are higher */
int higher(void *high, void *low) {
    Plane *highPtr = (Plane *) high; 
    Plane *lowPtr = (Plane *) low; 
    return highPtr->altitude >= lowPtr->altitude;
}

/* I figure out which of two passed-in planes are more westward */
int westmost(void *west, void *east) {
    Plane *westPtr = (Plane *) west; 
    Plane *eastPtr = (Plane *) east; 
    return westPtr->x <= eastPtr->x; 
}

/* Returns true if the given plane is outside Colorado */ 
int outside_colorado(void *data) {
    Plane *plane = (Plane *) data; 
    return !((plane->x >= 0 && plane->x < (COLORADO_WIDTH_MILES * FEET_PER_MILE)) 
        && (plane->y >= 0 && plane->y < (COLORADO_HEIGHT_MILES * FEET_PER_MILE))); 
}

/* Actions */ 
/* Deallocates plane data (will be called if it's outside Colorado) */
void dispose_plane(void *data) {
    Plane *plane = (Plane *) data;
    fprintf(stderr, "DIAGNOSTIC: %s leaves the simulation.\n", plane->callsign);
    free(plane); 
}

/* Prints a single line with all our plane data */ 
void print_plane(void *data) {
    Plane *plane = (Plane *) data;
    short xGrid = xToGrid(plane->x), yGrid = yToGrid(plane->y); 
    short flightLevel = getFlightLevelFromFeet(plane->altitude);
    fprintf(stderr, "%14s (%7.0lf, %7.0lf) (%3hd, %3hd) %5dft FL%3hd %4hdK H%3hd\n", plane->callsign, plane->x, plane->y, 
        xToGrid(plane->x), yToGrid(plane->y), plane->altitude, flightLevel, lround(plane->airspeed / FEET_PER_KNOT), plane->heading);
}

/* Draws a passed-in plane data with libatc */
void draw_plane(void *data) { 
    Plane *plane = (Plane *) data;
    al_plane(xToGrid(plane->x), yToGrid(plane->y), plane->callsign, getFlightLevelFromFeet(plane->altitude), (short) lround(plane->airspeed / FEET_PER_KNOT), plane->heading);
}

/* Calculates the new position of the plane */
void move_plane(void *data) { 
    Plane *plane = (Plane *) data;
    plane->altitude = plane->altitude + plane->roc; 
    plane->x = calcNewX(plane->x, plane->heading, plane->airspeed); 
    plane->y = calcNewY(plane->y, plane->heading, plane->airspeed);
}

/* Decides how we change plane direction/height */
void pilot_plane(void *data) {
    Plane *plane = (Plane *) data; 
    static void (*pilotFunctions[3])(Plane *) = {pilot0, pilot1, pilot2}; 
    pilotFunctions[plane->profile](plane);
}

/* Executes pilot code for flight profile zero */
void pilot0(Plane *plane) {
    /* Do nothing, we boring */
    fprintf(stderr, "DIAGNOSTIC: %s is flying straight and leveled off.\n", plane->callsign);
}

/* Executes pilot code for flight profile one */
void pilot1(Plane *plane) {
    pilot1HeadingChange(plane); 
    pilot1AltitudeChange(plane);    
}

/* If above 20500 feet, turn -15 deg each update */
void pilot1HeadingChange(Plane *plane) {    
    if (plane->altitude > 20500) {
        plane->heading -= 15; 
        if (plane->heading < 0) {
            plane->heading = 360 + plane->heading;
        }
        fprintf(stderr, "DIAGNOSTIC: %s is turning left and ", plane->callsign); 
    } else {
        fprintf(stderr, "DIAGNOSTIC: %s is flying straight and ", plane->callsign); 
    }
}

/* Above 19500 feet descend at -400 feet per minute */
void pilot1AltitudeChange(Plane *plane) {    
    if (plane->altitude > 19500) {
        plane->roc = -400; 
        fprintf(stderr, "descending.\n"); 
    } else {
        fprintf(stderr, "leveled off.\n");
    }
}

/* Executes pilot code for flight profile two */
void pilot2(Plane *plane) {
    pilot2HeadingChange(plane); 
    pilot2AltitudeChange(plane); 
}

/* Below 30500 turn 15 degrees each update */
void pilot2HeadingChange(Plane *plane) {    
    if (plane->altitude < 30500) {
        plane->heading += 15; 
        if (plane->heading > 360) {
            plane->heading = plane->heading % 360; 
        }
        fprintf(stderr, "DIAGNOSTIC: %s is turning right and ", plane->callsign); 
    } else {
        fprintf(stderr, "DIAGNOSTIC: %s is flying straight and ", plane->callsign);
    }
}

/* Below 33500 feet climb at 400 feet per minute */
void pilot2AltitudeChange(Plane *plane) {    
    if (plane->altitude < 33500) {
        plane->roc = 400; 
        fprintf(stderr, "climbing.\n");
    } else {
        fprintf(stderr, "leveled off.\n");
    }
}