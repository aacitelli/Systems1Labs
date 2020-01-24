#include <stdio.h>

int main() {
    printf("20 Degrees -> %d Degrees (Should be 70)\n", convertAngle(20));
    printf("70 Degrees -> %d Degrees (Should be 20)\n", convertAngle(70));
    printf("100 Degrees -> %d Degrees (Should be 350)\n", convertAngle(100));
    printf("180 Degrees -> %d Degrees (Should be 270)\n", convertAngle(180));
    printf("270 Degrees -> %d Degrees (Should be 180)\n", convertAngle(270));
    printf("315 Degrees -> %d Degrees (Should be 135)\n", convertAngle(315));
    return 0;
}

int convertAngle(int degrees) {
    int result = 90 - degrees;
    if (result < 0) {
        result = 360 + result;
    }
    return result;
}