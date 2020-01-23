#define COLORADO_WIDTH_MILES 380 
#define COLORADO_HEIGHT_MILES 280 
#define FEET_PER_MILE 5280 

#include <stdio.h>

/* Test isOverColorado with specific x-coordinates */
void testXFunctions() {
    /* X One Foot Left, X On Left Border, X In Middle, X On Right Border, X One Foot Right */
    printf("isOverColorado(-1, 0) => %d (Should Be 0)\n", isOverColorado(-1, 0));
    printf("isOverColorado(0, 0) => %d (Should Be 1)\n", isOverColorado(0, 0));
    printf("isOverColorado(200000, 0) => %d (Should Be 1)\n", isOverColorado(200000, 0));
    printf("isOverColorado((380 * 5280 - 1), 0) => %d (Should Be 1)\n", isOverColorado((380 * 5280 - 1), 0));
    printf("isOverColorado((380 * 5280), 0) => %d (Should Be 0)\n", isOverColorado((380 * 5280), 0));
}

/* Tests isOverColorado with specific y-coordinates */
void testYFunctions() {
    /* Y One Foot Left, Y On Left Border, Y In Middle, Y On Right Border, Y One Foot Right */
    printf("isOverColorado(0, -1) => %d (Should Be 0)\n", isOverColorado(0, -1));
    printf("isOverColorado(0, 0) => %d (Should Be 1)\n", isOverColorado(0, 0));
    printf("isOverColorado(, 200000) => %d (Should Be 1)\n", isOverColorado(0, 200000));
    printf("isOverColorado(0, 280 * 5280 - 1) => %d (Should Be 1)\n", isOverColorado(0, 280 * 5280 - 1));
    printf("isOverColorado(280 * 5280, 0) => %d (Should Be 0)\n", isOverColorado(0, 280 * 5280));
}

/* Tests the isOverColorado function */
int main() {
    testXFunctions(); 
    testYFunctions();
    return 0;
}

/* Reports whether fed-in x,y coordinates (in feet) are in colorado */
int isOverColorado(int x, int y) {
    return (x >= 0 && x < (COLORADO_WIDTH_MILES * FEET_PER_MILE)) && (y >= 0 && y < (COLORADO_HEIGHT_MILES * FEET_PER_MILE));  
}