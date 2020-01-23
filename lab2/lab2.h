/* Core Functionality */
void execSimulation();
void startPlanes();
void drawPlane(char planeName[], int xPosMiles, int yPosMiles, 
    short flightLevel, short airspeed, short heading);

/* Equations of motion */
int calcNewX(int oldX, short currAngle, short planeSpeedKnots, float dt);
int calcNewY(int oldY, short currAngle, short planeSpeedKnots, float dt);

/* Misc. utility functions */
int isOverColorado(int x, int y);
int getFlightLevelFromFeet(int feet);
short xToGrid(int x); 
short yToGrid(int y);