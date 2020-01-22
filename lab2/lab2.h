/* Organizational / libatc integration */
void execSimulation();
void execFrame(short currentTime);
void displayInput();

/* Equations of motion */
int calcNewX(int oldX, short currAngle, short planeSpeedKnots, float dt);
int calcNewY(int oldY, short currAngle, short planeSpeedKnots, float dt);

/* Misc. utility functions */
int isOverColorado(int currX, int currY);
short xMilestoGrid(int xPosMiles); 
short yMilesToGrid(int yPosMiles);

/* Core functionality */ 
void startPlanes();
void drawPlane(char planeName[], int xPosMiles, int yPosMiles, 
    short flightLevel, short airspeed, short heading);