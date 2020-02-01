/* 
    Purpose of this file:

    Create and initialize a structure and then pass the 
    address of the structure to a function that outputs the 
    plane data from the structure.

    (I also test out passing the structure by value)
*/

#include <stdio.h>

typedef struct Plane {
    char *planeName; 
    int x, y;
    short altitude, airspeed, heading;
} Plane; 

void initStructValues(struct Plane *planeStruct); 
void printStructValues(struct Plane planeStruct);
void printStructValuesByReference(struct Plane *planeStruct);

int main() {
    struct Plane planeStruct; 
    initStructValues(&planeStruct);
    printStructValues(planeStruct);
    printStructValuesByReference(&planeStruct);
}

void initStructValues(struct Plane *planeStruct) {
    planeStruct->airspeed = 1; 
    planeStruct->x = 2; 
    planeStruct->y = 3; 
    planeStruct->altitude = 4; 
    planeStruct->heading = 5; 
    planeStruct->planeName = "testPlane";
}

void printStructValues(struct Plane planeStruct) {
    fprintf(stdout, "Airspeed: %hd\n", planeStruct.airspeed);
    fprintf(stdout, "X Coordinate: %d\n", planeStruct.x);
    fprintf(stdout, "Y Coordinate: %d\n", planeStruct.y);
    fprintf(stdout, "Altitude: %hd\n", planeStruct.altitude);
    fprintf(stdout, "Heading: %hd\n", planeStruct.heading);
    fprintf(stdout, "Plane Name: %s\n", planeStruct.planeName);
}

void printStructValuesByReference(struct Plane *planeStruct) {
    fprintf(stdout, "Airspeed: %hd\n", planeStruct -> airspeed);
    fprintf(stdout, "X Coordinate: %d\n", planeStruct -> x);
    fprintf(stdout, "Y Coordinate: %d\n", planeStruct -> y);
    fprintf(stdout, "Altitude: %hd\n", planeStruct -> altitude);
    fprintf(stdout, "Heading: %hd\n", planeStruct -> heading);
    fprintf(stdout, "Plane Name: %s\n", planeStruct -> planeName);
}