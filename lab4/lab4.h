/* System libraries */
#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include <string.h>

/* Our personal libraries */ 
#include "structs.h"
#include "linkedlist.h" 
#include "libatc.h"
#include "altmem.h"
#include "sequencer.h"

/* Subheaders */
#include "functionPointers.h"
#include "planesMemory.h"
#include "utility.h"

#ifndef LAB3_H
#define LAB3_H

SequenceMachine *initializeSequenceMachineObject(SequenceMachine *sm, Simulation *simPtr); 
Simulation *fillSimObject(Simulation *simPtr, int argc, char **argv);
void attemptSim(Simulation *simPtr);
void readPlanes(Simulation *simPtr);
void fillPlaneValues(Plane *plane, char callsign[], double x, double y, int altitude, double airspeed, short heading, int profile); 
void addPlane(Plane *plane, Simulation *simPtr);
void flyPlanes(Simulation *simPtr);
void outputPlanes(Simulation *simPtr);
void drawPlanes(Simulation *simPtr);
void printHeaderInformation(Simulation *simPtr);
void printPlanes(Simulation *simPtr);

#endif 

