// largest

#include <stdio.h>

int main() {
    int largest_so_far = 0, last_input = 0;

    printf("Enter a number: ");
    scanf("%d", &last_input);
    while (last_input != 0) {
        if (last_input > largest_so_far) {
            largest_so_far = last_input;
        }

        printf("Enter a number: ");
        scanf("%d", &last_input);
    }

    printf("The largest number entered was: %d\n", largest_so_far);
}
