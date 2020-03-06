#include "structs.h"

#ifndef PLANESMEMORY_H
#define PLANESMEMORY_H

Plane *allocatePlane(Simulation *simPtr); 
void freePlane(Plane *plane, Simulation *simPtr); 

#endif 