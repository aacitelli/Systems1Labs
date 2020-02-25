#include "structs.h"

#ifndef UTILITY_H 
#define UTILITY_H

float degToRad(short degrees);
short convertAngle(short degrees);
double calcNewX(double oldX, short currAngle, double planeSpeedFeet);
double calcNewY(double oldY, short currAngle, double planeSpeedFeet);
short xToGrid(double x);
short yToGrid(double y);
short getFlightLevelFromFeet(int feet);
void outputPlaneContents(Plane *plane); 

#endif 