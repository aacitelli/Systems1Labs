/* 
    Purpose of this file:

    Create and initialize a structure and then pass the 
    address of the structure to a function that outputs the 
    plane data from the structure.
*/
typedef struct Plane {
    char *planeName; 
    int x, y;
    short altitude, airspeed, heading;
}; 

int main() {
    Plane x; 
    
}