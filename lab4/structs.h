#ifndef STRUCTS_H
#define STRUCTS_H

/* Need for FILE object */
#include <stdio.h>

typedef struct {
    void *storagePointer; 
    int elapsedTime, currentTenthOfSecond; 
    FILE *diagStream, *textStream, *inputStream; 
    
    int argc; 
    char **argv; 
} Simulation;

typedef struct {
    char *callsign; 
    double x, y, airspeed; 
    int profile, altitude, roc;
    short heading;  
    Simulation *pointerToSim; 
} Plane; 

#endif