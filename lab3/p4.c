/* 
    Purpose of this prototype: 

    Testing out how to pass stuff to the linked list. Reads in planes from the 
    linked list, puts them in in altitude order, then does graphical output once. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h" 
#include "linkedlist.h"
#include "planesMemory.h"

#define M_PI 3.14159265358979323846
#define FEET_PER_MILE 5280
#define FEET_PER_KNOT 1.687809855643
#define COLORADO_WIDTH_MILES 380
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_WIDTH_FEET (COLORADO_WIDTH_MILES * FEET_PER_MILE)
#define COLORADO_HEIGHT_FEET (COLORADO_HEIGHT_MILES * FEET_PER_MILE)
#define CHANGE_IN_TIME 60 

int higher(void *high, void *low) {
    Plane *highPtr = (Plane *) high; 
    Plane *lowPtr = (Plane *) low; 
    return highPtr->altitude > lowPtr->altitude;
}

void doStuff(Simulation *simPtr, Plane *plane1Ptr, Plane *plane2Ptr) {
    ComparisonFunction compare = higher; 
    insert(&simPtr, plane1Ptr, compare);
    insert(&simPtr, plane2Ptr, compare);
}

int main() {
    Plane *plane1, *plane2; 
    Simulation *simPtr = (Simulation *) malloc(sizeof(Simulation)); 
    if (simPtr == NULL) {
        fprintf(stderr, "Couldn't allocate memory for Simulation struct!\n"); 
        return -1; 
    }

    plane1 = (Plane *) allocatePlane(); 
    plane2 = (Plane *) allocatePlane(); 

    doStuff(simPtr, plane1, plane2); 

    freePlane(plane1); 
    freePlane(plane2); 
}

