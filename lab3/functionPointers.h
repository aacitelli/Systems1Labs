#include "lab3.h"
int convertAngle(int degrees); 
int calcNewX(int oldX, short currAngle, short planeSpeedFeet, float dt); 
int calcNewY(int oldY, short currAngle, short planeSpeedFeet, float dt);
short xToGrid(int x);
short yToGrid(int y);
int getFlightLevelFromFeet(int feet);
int higher(Plane *high, Plane *low);
int westmost(Plane *west, Plane *east);
int always(Plane *data);
int outside_colorado(Plane *data);
void dispose_plane(Plane *data);
void pilot_input(Plane *data);
void print_plane(Plane *data);
void draw_plane(Plane *data);
void move_plane(Plane *data);