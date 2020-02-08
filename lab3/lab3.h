/* Our personal libraries */ 
#include "structs.h"
#include "linkedlist.h" 
#include "libatc.h" 

/* System libraries */
#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 

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

/* Functions used elsewhere in the code */
int higher(Plane *high, Plane *low);
int westmost(Plane *west, Plane *east);
int always(Plane *data);
int outside_colorado(Plane *data);
void dispose_plane(Plane *data);
void pilot_input(Plane *data);
void print_plane(Plane *data);
void draw_plane(Plane *data);
void move_plane(Plane *data);