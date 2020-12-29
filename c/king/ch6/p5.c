// reverse

#include <stdio.h>

int main() {
    while (1) {
        printf("Enter a number: ");
        int input;
        scanf("%d", &input);

        printf("Reversed: ");
        while (input > 0) {
            printf("%d", input % 10);
            input /= 10;
        }
        printf("\n\n");
    }
}
