/* Imports, etc. */ 
#include "structs.h"
#include <stdio.h>
#include "libatc.h"
#include "sequencer.h"

/* add new items here */
void init_sequencer(SequenceMachine *sm)
{
    /* the following 2 lists must be kept in lockstep */
    initializer init[] = {param_count, open_diagnostics, open_text, open_input, init_graphics};
    shutdown_function final[] = {do_nothing, close_diagnostics, close_text, close_input, shutdown_graphics};
    
    int i;
    sm->at = 0;
    sm->count = sizeof(init) / sizeof(init[0]);

    for(i=0; i< sm->count; i++) {
        sm->entries[i].startup = init[i];
        sm->entries[i].shutdown = final[i];
    }
}

/* Initializes everything in the SequenceMachine */
int masterInit(SequenceMachine *sm) {

    int i; 
    for (i = 0; i < sm->count; i++) { 
        sm->at = i; 

        if (!sm->entries[i].startup(sm->simPtr)) {
            return 0; 
        }
    }

    return 1; 
}

/* Runs the sequencer shutdown procedure */
void masterShutdown(SequenceMachine *sm) {
    
    int j; 
    for (j = sm->at - 1; j >= 0; j--) {
        sm->entries[j].shutdown(sm->simPtr); 
    }
}

/* Checks that the number of passed-in parameters is correct */
int param_count(Simulation *simPtr) {

    /* Diagnostics pointer hasn't been opened yet; Supposed to default to stdout */
    if (simPtr->argc == 4) {
        /* Supposed to default to stdout if diagnostics haven't been opened yet; textStream points to stdout by default */
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: parameter count SUCCESS\n"); 
    } else {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: parameter count FAIL\n");
    }

    return simPtr->argc == 4; 
}

/* Opens the diagnostics file */
int open_diagnostics(Simulation *simPtr) {
 
    simPtr->diagStream = fopen(simPtr->argv[3], "w"); 
    if (simPtr->diagStream != NULL) {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: Open file err for diagnostics SUCCESS\n");
    } else {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: Open file err for diagnostics FAIL\n");
    }

    return simPtr->diagStream != NULL; 
}

/* Opens the general output file */
int open_text(Simulation *simPtr) {

    simPtr->textStream = fopen(simPtr->argv[2], "w");
    if (simPtr->textStream != NULL) {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: Open text file for text output SUCCESS\n");
    } else {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: Open text file for text output FAIL\n");
    }

    return simPtr->textStream != NULL; 
}

/* Initializes the input file */
int open_input(Simulation *simPtr) {

    simPtr->inputStream = fopen(simPtr->argv[1], "r");
    if (simPtr->textStream != NULL) {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: Open file 4jets.input for input SUCCESS\n");
    } else {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: Open file 4jets.input for input FAIL\n");
    }

    return simPtr->inputStream != NULL;
}

/* Initializes graphics with libatc */
int init_graphics(Simulation *simPtr) {
    int initValue = al_initialize(); 
    if (initValue == 0) {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: al_init() FAIL\n");
        fprintf(simPtr->diagStream, "ERROR: Couldn't initialize graphics! Error Code %d\n", initValue);
        return 0; 
    } else {
        fprintf(simPtr->diagStream, "DIAGNOSTIC: Startup: al_init() SUCCESS\n");
        fprintf(simPtr->diagStream, "Drawable area is (%d, %d) to (%d, %d)\n", al_min_X(), al_min_Y(), al_max_X(), al_max_Y());
        return 1;
    }
}

/* Just a placeholder function to avoid an off-by-one error */
void do_nothing(Simulation *simPtr) {
    fprintf(simPtr->diagStream, "DIAGNOSTIC: Shutdown: do nothing called\n");
}

/* Closes the diagnostics file */
void close_diagnostics(Simulation *simPtr) {
    fprintf(simPtr->diagStream, "DIAGNOSTIC: Shutdown: Close diagnostics file err\n");
    fclose(simPtr->diagStream); 
}

/* Closes the general output file */
void close_text(Simulation *simPtr) {
    fprintf(simPtr->diagStream, "DIAGNOSTIC: Shutdown: Close text output file text\n");
    fclose(simPtr->textStream); 
}

/* Closes the input file */
void close_input(Simulation *simPtr) {
    fprintf(simPtr->diagStream, "DIAGNOSTIC: Shutdown: Close input file 4jets.input\n");
    fclose(simPtr->inputStream);
}

/* Shuts down graphics for libatc */
void shutdown_graphics(Simulation *simPtr) {
    fprintf(simPtr->diagStream, "DIAGNOSTIC: Shutdown: calling al_teardown()\n");
    al_teardown();
}