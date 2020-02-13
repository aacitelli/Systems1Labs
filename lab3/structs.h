#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    void *storagePointer; 
    int elapsedTime; 
} Simulation;

typedef struct {
    char *planeName; 
    double x, y, airspeed; 
    int profile, altitude, roc;
    short heading;  
    Simulation *pointerToSim; 
} Plane; 

#endif