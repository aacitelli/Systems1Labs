/* System libraries */
#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 

/* Our personal libraries */ 
#include "structs.h"
#include "linkedlist.h" 
#include "libatc.h"
#include "altmem.h"

/* Subheaders */
#include "functionPointers.h"
#include "planesMemory.h"
#include "utility.h"

#ifndef LAB3_H
#define LAB3_H

void attemptSim(); 
void readPlanes(Simulation *simPtr);
void fillDefaultValues(Plane *plane, Simulation *simPtr); 
void addPlane(Plane *plane, Simulation *simPtr);
void flyPlanes(Simulation *simPtr); 
void outputPlanes(Simulation *simPtr); 
void drawPlanes(Simulation *simPtr); 
void printHeaderInformation(Simulation *simPtr); 
void printPlanes(Simulation *simPtr); 

#endif 

