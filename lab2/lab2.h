/* Organizational / Control Level */
void inputLoop();
void timerLoop(char planeName[], int x, int y, int altitude, short airspeed, short heading, FILE *output);
void atcStartup(); 
void atcTeardown(); 
void drawPlane(char planeName[], int x, int y, short altitude, short airspeed, short heading); 

/* Unit Conversions, Other Utility */
int calcNewX(int oldX, short currAngle, short planeSpeedKnots, float dt); 
int calcNewY(int oldY, short currAngle, short planeSpeedKnots, float dt); 
short xToGrid(int x); 
short yToGrid(int y);
int getFlightLevelFromFeet(int feet); 
int isOverColorado(int x, int y);
int convertAngle(int degrees); 
float degToRad(int degrees);

/* Output */
void output(short time, char planeName[], int x, int y, int altitude, short airspeed, short heading, FILE *output);
void printHeaderInformation(FILE *output);