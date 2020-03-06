/* Prototype by Anden Acitelli.2 */ 
/* The purpose of this prototype is to test that plane allocation still 
    works, even with alternative_malloc. It's more just exploring how it works
    before I get started with the lab. */ 

#include "structs.h"
#include "planesMemory.h"

int main() {
    Simulation simObj; 
    simObj.diagStream = stdout;
    int i; 
    int numPlanesTotal = 10; 
    int numPlanesActuallyAllocated = 0; 
    for (i = 0; i < 10; i++) {
        Plane *plane = allocatePlane(&simObj);
        if (plane != NULL) {
            numPlanesActuallyAllocated++;
        }
    }

    /* This should be somewhere between 1 and 10. Some should fail, some should pass. */
    fprintf(stdout, "Num Planes Total: %d\n", numPlanesTotal); 
    fprintf(stdout, "Num Planes Actually Allocated: %d\n", numPlanesActuallyAllocated);
}