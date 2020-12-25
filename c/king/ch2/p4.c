// tax calculator

#include <stdio.h>

#define TAX_RATE 0.05f

int main() {
    printf("Tax rate is %.2f\n", TAX_RATE);
    while (1) {
        float input_amount = 0;
        printf("Enter an amount: ");
        scanf("%f", &input_amount);
        printf("With tax added: $%.2f\n\n", (1 + TAX_RATE) * input_amount);
    }
}
