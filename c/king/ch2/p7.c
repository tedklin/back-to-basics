// bill counter

#include <stdio.h>

int main() {
    while (1) {
        int input_amount = 0;
        printf("Enter a dollar amount: ");
        scanf("%d", &input_amount);

        int leftover_amount = input_amount;
        printf("$20 bills: %d\n", leftover_amount / 20);
        leftover_amount %= 20;
        printf("$10 bills: %d\n", leftover_amount / 10);
        leftover_amount %= 10;
        printf("$5 bills: %d\n", leftover_amount / 5);
        leftover_amount %= 5;
        printf("$1 bills: %d\n", leftover_amount);
    }
}
