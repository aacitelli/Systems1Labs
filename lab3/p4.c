/* 
    Purpose of this prototype: 

    Allocates every plane from the stdin stream, checking for memory
    allocation failures and outputting diagnostic information 
    if anything fails. 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Plane {
    char planeName[41]; /* 40 letters + \0 */
    int x, y;
    short altitude, airspeed, heading;
} Plane; 

void *readInPlanes(Plane *planeArray[]); 
void printPlanes(); 

int main() {
    Plane *planeArray[255]; 
    readInPlanes(planeArray);
    printPlanes(planeArray);
}

void *readInPlanes(Plane **planeArray) {
    int i = 0, input; /* Tracks which plane index we're on */

    /* Allocating space for our first plane and throwing errors if memory allocation failed */
    planeArray[i] = malloc(sizeof(Plane));
    if (planeArray[i] == NULL) {
        fprintf(stderr, "Couldn't allocate plane %d!\n", (i + 1));
    } 

    /* Actually reading in the first plane */
    input = scanf("%s %d %d %hd %hd %hd", planeArray[i]->planeName, &(planeArray[i]->x), &(planeArray[i]->y), 
            &(planeArray[i]->altitude), &(planeArray[i]->airspeed), &(planeArray[i]->heading));

    while (input != EOF) {

        /* If we got here, we read in the next plane successfully, so we can report a success message for it then move to the next one */
        fprintf(stdout, "Plane %d read in!\n", i + 1);
        i++;

        /* Allocate space for next place and ensure it was allocated correctly */
        planeArray[i] = malloc(sizeof(Plane));
        if (planeArray[i] == NULL) {
            fprintf(stderr, "Couldn't allocate plane %d!\n", (i + 1));
        }

        /* Actually read in next plane */
        input = scanf("%s %d %d %hd %hd %hd", planeArray[i]->planeName, &(planeArray[i]->x), &(planeArray[i]->y), 
            &(planeArray[i]->altitude), &(planeArray[i]->airspeed), &(planeArray[i]->heading));
    }

    return planeArray;
}

void printPlanes(Plane **planeArray) {
    int i; 

    /* TODO: Modify this to intelligently stop as far as the number of planes goes so 
        that it doesn't revert to whatever was happening before */
    for (i = 0; i < 10; i++) {

    }
}

/* 
    Allocate space for the initial plane, returning if it fails  

    Read in the initial plane

    while (!EOF) {
        Say that we read in that plane correctly 

        Preemptively allocate pointer space for the next plane 

        Actually read in the next plane 
    }
*/

