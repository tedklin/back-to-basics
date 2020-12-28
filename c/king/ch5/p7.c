// four ints

#include <stdio.h>

int main() {
    while (1) {
        printf("Enter four integers: ");

        int arr[4];
        for (int i = 0; i != 4; i++) {
            scanf("%d", arr + i);
        }

        int smallest = arr[0], largest = arr[0];
        for (int i = 1; i != 4; i++) {
            if (arr[i] < smallest) {
                smallest = arr[i];
            }
            if (arr[i] > largest) {
                largest = arr[i];
            }
        }

        printf("Smallest: %d\nLargest: %d\n\n", smallest, largest);
    }
}
