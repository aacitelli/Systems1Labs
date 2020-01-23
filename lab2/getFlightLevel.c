#include <stdio.h>

/* Tests the isOverColorado function, testing rounding up/down */
int main() {
    printf("Round 6200 Result (Should Be 60): %i\n", getFlightLevelFromFeet(6200));
    printf("Round 6300 Result (Should be 65): %i\n", getFlightLevelFromFeet(6300));
    printf("Round 6250 Result (Should be 65): %i\n", getFlightLevelFromFeet(6250));
    return 0;
}

/* Returns the flight level given a feet amount */
int getFlightLevelFromFeet(int feet) {
    if (feet % 500 < 250) {
        return (feet - (feet % 500)) / 100; 
    } else {
        return (feet + (500 - feet % 500)) / 100;
    }
}

