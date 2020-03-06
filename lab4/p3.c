/* Prototype by Anden Acitelli.2 */ 
/* The purpose of this prototype is to test that file streams can be 
    correctly stored inside a structure, like I plan to do in the lab. */ 

#include "structs.h"
#include <stdio.h> 

int main() {
    Simulation simObj; 
    simObj.diagStream = fopen("p3file.txt", "w"); 
    if (simObj.diagStream == NULL) {
        fprintf(stdout, "File stream not assigned properly to object!\n"); 
    } else {
        fprintf(stdout, "File stream assigned properly.\n");
        fclose(simObj.diagStream);
    }
}