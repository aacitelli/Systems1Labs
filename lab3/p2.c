/* 
    Prototype function: 

    Read in the three values into a simulation structure 
    with any derived data that you desire.
*/

#include <stdio.h>
#include <stdlib.h>

/* FOR THE PROGRAM ITSELF, IT'S LESS COMPLICATED TO JUST USE 
    char name[41]!; */
typedef struct SimulationData {
    char *name;
    double timeElapsed;
    int frameRate, speedUpFactor; 
    void *storagePointer; 
} SimulationData;

void fillSimulationData(struct SimulationData *data); 
void printSimulationData(struct SimulationData *data);

int main() {
    struct SimulationData simData; 
    fillSimulationData(&simData);
    printSimulationData(&simData);
}

void fillSimulationData(struct SimulationData *data) {
    /* We just store this as a pointer, so we need to actually allocate memory
        so the program isn't writing to undeclared memory */
    data->name = malloc(41 * sizeof(char));
    scanf("%s %d %d", data->name, &(data->frameRate), &(data->speedUpFactor));
}

void printSimulationData(struct SimulationData *data) {
    fprintf(stdout, "Simulation Name: %s\n", data->name);
    fprintf(stdout, "Frame Rate: %d\n", data->frameRate); 
    fprintf(stdout, "Speed Up Factor: %d\n", data->speedUpFactor);
}