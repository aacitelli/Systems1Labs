typedef struct Simulation {
    void *storagePointer; 
    int elapsedTime; 
} Simulation;

typedef struct Plane {
    char *planeName; 
    double x, y, altitude, airspeed; 
    int profile;
    short heading;  
    Simulation *pointerToSim; 
} Plane; 