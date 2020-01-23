/* what are the drawable x and Y values ? */
int al_min_X();
int al_min_Y();

int al_max_X();
int al_max_Y();

void al_clock(int elapsed_seconds);

/* check the return value on init before drawing */
int al_initialize();
/* just before our program exits, return the tuerminal to normal */
void al_teardown();

/* if init gave us a good drawing canvas, clear it before drawing */
void al_clear();
/* to commit all drawings to the screen, call al_refresh */
void al_refresh();

/* put a plane on screen */
void al_plane(int gx, int gy, char *callsign, short FL, short knots, 
		short heading);

/* not required for lab2 */
void al_status(const char *statstr);
int al_version();

