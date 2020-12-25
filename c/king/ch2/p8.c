// loan calculator

#include <stdio.h>

int main() {
    while (1) {
        float loan_balance = 0, interest_rate = 0, monthly_payment = 0;
        printf("Enter amount of loan: ");
        scanf("%f", &loan_balance);
        printf("Enter interest rate: ");
        scanf("%f", &interest_rate);
        printf("Enter monthly payment: ");
        scanf("%f", &monthly_payment);

        float monthly_interest = interest_rate / 100.0f / 12.0f;

        for (int i = 1; i != 4; ++i) {
            loan_balance += loan_balance * monthly_interest - monthly_payment;
            printf("Balance remaining after %d payments: $%.2f\n", i, loan_balance);
        }
        printf("\n");
    }
}
