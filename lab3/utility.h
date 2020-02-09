#ifndef UTILITY_H 
#define UTILITY_H

float degToRad(int degrees);
int convertAngle(int degrees);
int calcNewX(int oldX, short currAngle, short planeSpeedFeet, float dt);
int calcNewY(int oldY, short currAngle, short planeSpeedFeet, float dt);
short xToGrid(int x);
short yToGrid(int y);
int getFlightLevelFromFeet(int feet);

#endif 