// even squares

#include <stdio.h>

int main() {
    printf("Enter a number: ");
    int input;
    scanf("%d", &input);

    printf("All even squares in (1, %d]:\n", input);
    for (int i = 2; i * i <= input; i += 2) {
        printf("%d\n", i * i);
    }
}
