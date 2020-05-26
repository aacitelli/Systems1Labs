/* instructor provided C code file for lab5 */
#include <stdio.h>

long transitions(long i);

main() {
    long i, cnt;
    printf("Enter an integer: ");
    scanf("%ld", &i);
    cnt = transitions(i);
    printf("%ld has %ld transitions.\n", i, cnt);
}