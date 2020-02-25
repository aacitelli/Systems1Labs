/* System libraries */
#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 

/* Our personal libraries */ 
#include "structs.h"
#include "linkedlist.h" 
#include "libatc.h"

/* Subheaders */
#include "functionPointers.h"
#include "planesMemory.h"
#include "utility.h"

#ifndef LAB3_H
#define LAB3_H

void attemptSim(); 
void readPlanes(Simulation *simPtr);
void addPlane(char *planeName, double x, double y, int altitude, double airspeed, short heading, int pilotProfile, Simulation *simPtr);
void flyPlanes(Simulation *simPtr); 
void outputPlanes(Simulation *simPtr); 
void drawPlanes(Simulation *simPtr); 
void printHeaderInformation(Simulation *simPtr); 
void printPlanes(Simulation *simPtr); 
void fillPlaneData(Plane *plane, char *planeName, double x, double y, double airspeed, int profile, int altitude, short heading, Simulation *simPtr);

#endif 

