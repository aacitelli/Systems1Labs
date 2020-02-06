/* 
    Purpose of this prototype: 
    Write a function to test using a static storage 
    block scope variable. It would increment each time 
    the function is called and print that count.
*/

#include <stdio.h> 

void printValueOfStaticVariable();

int main() {
    int i;
    for (i = 0; i < 10; i++) {
        printValueOfStaticVariable();
    }
}

void printValueOfStaticVariable() {
    static int count = 0; 
    count++; 
    fprintf(stdout, "%d\n", count);
}