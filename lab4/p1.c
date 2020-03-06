/* Prototype by Anden Acitelli.2 */ 
/* The purpose of this prototype is to test that I am opening and closing files correctly. */ 
#include <stdio.h> 
int main() {
    FILE *filePtr = fopen("p1testfile.txt", "w"); 
    fprintf(filePtr, "Hey look I printed!\n"); 
    fclose(filePtr);
}