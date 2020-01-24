#define FEET_PER_MILE 5280
#define COLORADO_HEIGHT_MILES 280
#define COLORADO_HEIGHT_FEET (280 * 5280)
#define COLORADO_WIDTH_MILES 380 
#define COLORADO_WIDTH_FEET (380 * 5280)

#include <math.h> 
#include <stdio.h>
#include "libatc.h"

void testXConversions(); 
void testYConversions();
short xToGrid(int x); 
short yToGrid(int y);

/* Runs the program */
int main() {
    int initValue = al_initialize(); 
    if (initValue != 0) {
        testXConversions(); 
        testYConversions();
    } else {
        fprintf(stderr, "Failed to initialize libatc! Error Code %d\n", initValue);
        return initValue;
    }
    
    return 0; 
}

/* Tests xToGrid() with minimum, intermediate, and maximum bounds */
void testXConversions() {
    fprintf(stderr, "Horizontal Conversion Testing:\n");
    fprintf(stderr, "X Bounds: (%d, %d)\n", al_min_X(), al_max_X());
    fprintf(stderr, "0 Feet: Grid Column %hd\n", xToGrid(0));
    fprintf(stderr, "1003200 (~Halfway) Feet: Grid Column %i\n", xToGrid(380 * 5280 / 2));
    fprintf(stderr, "2006400 - 1 (~One Foot From Edge) Feet: Grid Column %i\n", xToGrid(380 * 5280 - 1));
}

/* Tests yToGrid() with minimum, intermediate, and maximum bounds */
void testYConversions() {
    fprintf(stderr, "Vertical Conversion Testing:\n");
    fprintf(stderr, "Y Bounds: (%d, %d)\n", al_min_Y(), al_max_Y());
    fprintf(stderr, "0 Feet: Grid Column %hd\n", yToGrid(0));
    fprintf(stderr, "739200 (~Halfway) Feet: Grid Column %i\n", yToGrid(280 * 5280 / 2));
    fprintf(stderr, "1478400 - 1 (~One Foot From Edge) Feet: Grid Column %i\n", yToGrid(280 * 5280 - 1));
}

/* Converts passed-in feet amount to *horizontal* grid units */
short xToGrid(int x) {
    short minX = al_min_X(), maxX = al_max_X();
    short gridWidth = maxX - minX;
    return lround(minX + ((float) x * (1.0 / COLORADO_WIDTH_FEET) * (gridWidth / 1.0))); 
}

/* Converts passed-in feet amount to *vertical* grid units */
short yToGrid(int y) {
    short minY = al_min_Y(), maxY = al_max_Y();
    short gridHeight = maxY - minY;
    return (1 + maxY) - lround(minY + ((float) y * (1.0 / COLORADO_HEIGHT_FEET) * (gridHeight / 1.0)));
}