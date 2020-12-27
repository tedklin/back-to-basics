// upc

#include <stdio.h>

int main() {
    while (1) {
        printf("Enter the first 11 digits of a UPC: ");

        int first_digit;
        scanf("%1d", &first_digit);

        int group_1[5];
        int group_2[5];
        for (int i = 0; i != 5; i++) {
            scanf("%1d", group_1 + i);
        }
        for (int i = 0; i != 5; i++) {
            scanf("%1d", group_2 + i);
        }

        int first_sum = first_digit + group_1[1] + group_1[3]
            + group_2[0] + group_2[2] + group_2[4];
        int second_sum = group_1[0] + group_1[2] + group_1[4]
            + group_2[1] + group_2[3];
        int total = 3 * first_sum + second_sum;

        printf("Check digit: %d\n\n", 9 - ((total - 1) % 10));
    }
}
