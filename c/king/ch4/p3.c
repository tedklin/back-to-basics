// reverse digits

#include <stdio.h>

int main() {
    while (1) {
        printf("Enter a 3-digit number: ");
        int digit_1, digit_2, digit_3;
        scanf("%1d%1d%1d", &digit_1, &digit_2, &digit_3);
        printf("Reversed: %1d%1d%1d\n\n", digit_3, digit_2, digit_1);
    }
}
