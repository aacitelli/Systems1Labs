typedef struct {
    void *storagePointer; 
    int elapsedTime; 
} Simulation;

typedef struct {
    char *planeName; 
    double x, y, altitude, airspeed; 
    int profile;
    short heading;  
    Simulation *pointerToSim; 
} Plane; 