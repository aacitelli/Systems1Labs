/* This prototype is for all my linked list functions. */ 
#include "linkedlist.h"
#include "structs.h"
#include "libatc.h"

/* Important Constants */
#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.687809855643
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_WIDTH_FEET (COLORADO_WIDTH_MILES * FEET_PER_MILE)
#define COLORADO_HEIGHT_FEET (COLORADO_HEIGHT_MILES * FEET_PER_MILE)
#define CHANGE_IN_TIME 60 

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

/* Returns the flight level given a feet amount */
int getFlightLevelFromFeet(int feet) {
    if (feet % 500 < 250) {
        return (feet - (feet % 500)) / 100; 
    } else {
        return (feet + (500 - feet % 500)) / 100;
    }
}

/* Comparison Functions */ 
int *higher(Plane *high, Plane *low) {
    return high->altitude > low->altitude; 
}

int *westmost(Plane *west, Plane *east) {
    return west->x < east->x; 
}

/* Criteria Functions */ 
/* Always returns true (used only for debug purposes) */
int *always(Plane *data) {
    return 1; 
} 

/* Returns true if the given plane is outside Colorado */ 
int *outside_colorado(Plane *data) {
    int isInColorado = (data->x >= 0 && data->x < (COLORADO_WIDTH_MILES * FEET_PER_MILE)) 
        && (data->y >= 0 && data->y < (COLORADO_HEIGHT_MILES * FEET_PER_MILE)); 
    return !isInColorado; 
}

/* Actions */ 
/* Deallocates plane data (will be called if it's outside Colorado) */
void *dispose_plane(Plane *data) {
    free(data); 
}

void *pilot_input(Plane *data) {

}

/* Prints a single line with all our plane data */ 
void *print_plane(Plane *data) {
    fprintf(stderr, "%14s ", data->planeName);
    fprintf(stderr, "(%7d, %7d) ", data->x, data->y);
    fprintf(stderr, "(%3hd, %3hd) ", xToGrid(data->x), yToGrid(data->y));
    fprintf(stderr, "%5dft ", data->altitude);
    fprintf(stderr, "FL%3hd ", getFlightLevelFromFeet(data->altitude));
    fprintf(stderr, "%4hdK ", lround(data->airspeed / FEET_PER_KNOT));
    fprintf(stderr, "H%3hd\n", data->heading);
}

/* Feeds all our plane data into al_plane to physically draw it on the canvas */ 
void *draw_plane(Plane *data) { 
    al_plane(data->planeName, xToGrid(data->x), yToGrid(data->y), data->altitude, data->airspeed, data->heading);
}

/* Calculates the new position of the plane */
void *move_plane(Plane *data) {
    switch(data->profile) {
        case 0: movePlaneProfile0(); 
        case 1: movePlaneProfile1(); 
        case 2: movePlaneProfile2(); 
        default: fprintf(stderr, "ERROR: Plane profile wasn't 0, 1, or 2! Can't move plane.\n");
    }
}

void *movePlaneProfile0() {

}

void *movePlaneProfile1() {

}

void *movePlaneProfile2() {

}

