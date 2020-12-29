// calendar

#include <stdio.h>

int main() {
    printf("Enter the number of days in month: ");
    int num_days;
    scanf("%d", &num_days);

    printf("Enter starting day of week (1=Sun,7=Sat): ");
    int start;
    scanf("%d", &start);

    for (int i = 1; i < start; i++) {
        printf("   ");
    }
    for (int i = 1; i <= num_days; i++) {
        printf("%2d", i);
        if ((i + start - 1) % 7 == 0) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}
