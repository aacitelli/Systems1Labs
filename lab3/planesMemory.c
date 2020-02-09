#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

/* This function allocates space for a single plane, printing diagnostic
    information and correctly throwing errors. */
Plane *allocatePlane() {
    static short numAllocates = 0; 
    Plane *planePtr = malloc(sizeof(Plane)); 
    if (planePtr == NULL) {
        fprintf(stderr, "ERROR: Could not manually allocate memory for plane!\n");
    } else {
        fprintf(stderr, "DIAGNOSTIC: allocatePlane: %hd planes allocated.\n", ++numAllocates); 
    }   
    return planePtr; 
}

/* This function frees the Plane represented by the passed-in pointer, 
    printing diagnostic information. */
void freePlane(Plane *plane) {
    static short numFrees = 0; 
    free(plane); 
    fprintf(stderr, "DIAGNOSTIC: freePlane: %hd planes recycled.\n", ++numFrees); 
}