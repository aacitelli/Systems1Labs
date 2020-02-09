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

void attemptSim(); 
void readPlanes(Simulation *simStruct);
void addPlane(char *planeName, double x, double y, double altitude, double airspeed, short heading, int pilotProfile, Simulation *simStruct);
void flyPlanes(Simulation *simPtr); 
void outputPlanes(Simulation *simPtr); 
void drawPlanes(Simulation *simPtr); 
void printHeaderInformation(); 
void printPlanes(Simulation *simPtr); 
void pilotPlane(); 
void movePlane(Plane *plane); 
float degToRad(int degrees);

