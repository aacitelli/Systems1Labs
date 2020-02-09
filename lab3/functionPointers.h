/* Using header guards to avoid double declarations */
#ifndef FUNCTIONPOINTERS_H
#define FUNCTIONPOINTERS_H

int convertAngle(int degrees); 
int calcNewX(int oldX, short currAngle, short planeSpeedFeet, float dt); 
int calcNewY(int oldY, short currAngle, short planeSpeedFeet, float dt);
short xToGrid(int x);
short yToGrid(int y);
int getFlightLevelFromFeet(int feet);
int higher(void *high, void *low);
int westmost(void *west, void *east);
int always(void *data);
int outside_colorado(void *data);
void dispose_plane(void *data);
void print_plane(void *data);
void draw_plane(void *data);
void move_plane(void *data);

#endif 