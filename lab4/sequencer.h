#ifndef SEQUENCER_H 
#define SEQUENCER_H 

#include "structs.h" 

/* Useful typedefs */
typedef int (*initializer)(Simulation *sim);
typedef void (*shutdown_function)(Simulation *sim);

typedef struct Pair {
    initializer startup; 
    shutdown_function shutdown; 
} Pair; 

typedef struct SequenceMachine {
    int at, count; 
    Pair entries[5];
    Simulation *simPtr;
} SequenceMachine; 

void init_sequencer(SequenceMachine *sm);
int masterInit(SequenceMachine *sm);
void masterShutdown(SequenceMachine *sm);
int param_count(Simulation *simPtr);
int open_diagnostics(Simulation *simPtr);
int open_text(Simulation *simPtr);
int open_input(Simulation *simPtr); 
int init_graphics(Simulation *simPtr);
void do_nothing(Simulation *simPtr);
void close_diagnostics(Simulation *simPtr);
void close_text(Simulation *simPtr);
void close_input(Simulation *simPtr);
void shutdown_graphics(Simulation *simPtr);

#endif 