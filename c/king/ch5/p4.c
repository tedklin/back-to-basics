// wind

#include <stdio.h>

int main() {
    while (1) {
        printf("Enter a wind speed in knots: ");
        float speed;
        scanf("%f", &speed);

        if (speed < 1) {
            printf("kalm...");
        } else if (speed <= 3) {
            printf("Light air");
        } else if (speed <= 27) {
            printf("Breeze");
        } else if (speed <= 47) {
            printf("Gale");
        } else if (speed <= 63) {
            printf("Storm");
        } else {
            printf("Hurricane");
        }
        printf("\n\n");
    }
}
