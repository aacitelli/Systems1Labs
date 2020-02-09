/* System libraries */ 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Our libraries */ 
#include "functionPointers.h"
#include "structs.h"
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
int higher(void *high, void *low) {
    Plane *highPtr = (Plane *) high; 
    Plane *lowPtr = (Plane *) low; 
    return highPtr->altitude > lowPtr->altitude; 
}

int westmost(void *west, void *east) {
    Plane *westPtr = (Plane *) west; 
    Plane *eastPtr = (Plane *) east; 
    return westPtr->x < eastPtr->x; 
}

/* Criteria Functions */ 
/* Always returns true (used only for debug purposes) */
int always(void *data) {
    Plane *plane = (Plane *) data; 
    return 1; 
} 

/* Returns true if the given plane is outside Colorado */ 
int outside_colorado(void *data) {
    Plane *plane = (Plane *) data; 
    int isInColorado = (plane->x >= 0 && plane->x < (COLORADO_WIDTH_MILES * FEET_PER_MILE)) 
        && (plane->y >= 0 && plane->y < (COLORADO_HEIGHT_MILES * FEET_PER_MILE)); 
    return !isInColorado; 
}

/* Actions */ 
/* Deallocates plane data (will be called if it's outside Colorado) */
void dispose_plane(void *data) {
    Plane *plane = (Plane *) data;
    free(plane); 
}

/* Prints a single line with all our plane data */ 
void print_plane(void *data) {
    Plane *plane = (Plane *) data;

    fprintf(stderr, "%14s ", plane->planeName);
    fprintf(stderr, "(%7d, %7d) ", plane->x, plane->y);
    fprintf(stderr, "(%3hd, %3hd) ", xToGrid(plane->x), yToGrid(plane->y));
    fprintf(stderr, "%5dft ", plane->altitude);
    fprintf(stderr, "FL%3hd ", getFlightLevelFromFeet(plane->altitude));
    fprintf(stderr, "%4hdK ", lround(plane->airspeed / FEET_PER_KNOT));
    fprintf(stderr, "H%3hd\n", plane->heading);
}

/* Feeds all our plane data into al_plane to physically draw it on the canvas */ 
void draw_plane(void *data) { 
    Plane *plane = (Plane *) data;

    fprintf(stderr, "--------------------------------------\n");
    fprintf(stderr, "draw_plane: About to draw the following plane:\n");       
    fprintf(stderr, "Name: %s\n", plane->planeName); 
    fprintf(stderr, "(x, y) in Feet: (%lf, %lf)\n", plane->x, plane->y); 
    fprintf(stderr, "Altitude in Feet: %lf\n", plane->altitude); 
    fprintf(stderr, "Airspeed in Feet: %lf\n", plane->airspeed); 
    fprintf(stderr, "Heading: %hd\n", plane->heading); 
    fprintf(stderr, "Flight Profile: %hd\n", plane->profile); 
    fprintf(stderr, "\n");

    al_plane(plane->planeName, xToGrid(plane->x), yToGrid(plane->y), 
        getFlightLevelFromFeet(plane->altitude), plane->airspeed, plane->heading);
}

/* Calculates the new position of the plane */
void move_plane(void *data) { 
    Plane *plane = (Plane *) data; 
    plane->x = calcNewX(plane->x, plane->heading, plane->airspeed, CHANGE_IN_TIME); 
    plane->y = calcNewX(plane->x, plane->heading, plane->airspeed, CHANGE_IN_TIME);
}