/* Organizational / Control Level */
void inputLoop();
void timerLoop(char planeName[], int x, int y, short fL, short airspeed, short heading);
void atcStartup(); 
void atcTeardown(); 
void drawPlane(char planeName[], int x, int y, short fL, short airspeed, short heading); 

/* Unit Conversions, Other Utility */
int calcNewX(int oldX, short currAngle, short planeSpeedKnots, float dt); 
int calcNewY(int oldY, short currAngle, short planeSpeedKnots, float dt); 
short xToGrid(int x); 
short yToGrid(int y);
int getFlightLevelFromFeet(int feet); 
int isOverColorado(int x, int y);