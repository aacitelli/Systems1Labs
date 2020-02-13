#include "structs.h"

#ifndef FUNCTIONPOINTERS_H
#define FUNCTIONPOINTERS_H

/* Comparison Functions */ 
int higher(void *high, void *low);
int westmost(void *west, void *east);
int outside_colorado(void *data);
void dispose_plane(void *data);
void print_plane(void *data);
void draw_plane(void *data);
void move_plane(void *data);
void pilot_plane(void *data);
void pilot0(Plane *plane);
void pilot1(Plane *plane);
void pilot1HeadingChange(Plane *plane);
void pilot1AltitudeChange(Plane *plane);
void pilot2(Plane *plane);
void pilot2HeadingChange(Plane *plane);
void pilot2AltitudeChange(Plane *plane);

#endif 