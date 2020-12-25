#include <stdio.h>

int main() {
    int height = 8, length = 12, width = 10;

    printf("Dimensions: %dx%dx%d\n", length, width, height);
    printf("Volume (cubic inches): %d\n", height * length * width);
    printf("Dimensional weight (pounds): %d\n", 
        (height * length * width + 165) / 166);

    return 0;
}
