#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include "altmem.h"

/* This function allocates space for a single plane, printing diagnostic
    information and correctly throwing errors. */
Plane *allocatePlane(Simulation *simPtr) {
    static short numAllocates = 0; 
    Plane *planePtr = (Plane *) alternative_malloc(sizeof(Plane)); 
    if (planePtr == NULL) {
        fprintf(simPtr->diagStream, "ERROR: Could not manually allocate memory for plane!\n");
    } else {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: allocatePlane: %hd planes allocated.\n", ++numAllocates); 
    }   
    return planePtr; 
}

/* This function frees the Plane represented by the passed-in pointer, 
    printing diagnostic information. */
void freePlane(Plane *plane, Simulation *simPtr) {
    static short numFrees = 0;
    alternative_free(plane);
    fprintf(simPtr->diagStream, "DIAGNOSTIC: freePlane: %hd planes recycled.\n", ++numFrees);
}