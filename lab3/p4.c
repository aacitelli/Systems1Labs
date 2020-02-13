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
    fprintf(stderr, "Declaring thing\n"); 
    fprintf(stderr, "Inserting first plane\n");
    insert(&(simPtr->storagePointer), plane1Ptr, higher);
    fprintf(stderr, "Inserting Second Plane\n");
    insert(&(simPtr->storagePointer), plane2Ptr, higher);
}

int main() {
    Plane *plane1, *plane2; 
    Simulation *simPtr = (Simulation *) malloc(sizeof(Simulation)); 
    if (simPtr == NULL) {
        fprintf(stderr, "Couldn't allocate memory for Simulation struct!\n"); 
        return -1; 
    }

    fprintf(stderr, "About to allocate first plane.\n");
    plane1 = (Plane *) allocatePlane(); 
    fprintf(stderr, "About to allocate second plane.\n");
    plane2 = (Plane *) allocatePlane(); 

    fprintf(stderr, "About to do stuff.\n");
    doStuff(simPtr, plane1, plane2); 

    fprintf(stderr, "About to free plane 1.\n");
    freePlane(plane1); 
    fprintf(stderr, "About to free plane 2.\n");
    freePlane(plane2); 
}

