// date

#include <stdio.h>

int main() {
    while (1) {
        int month = 0, day = 0, year = 0;
        printf("Enter a date (mm/dd/yyyy): ");
        scanf("%d/%d/%d", &month, &day, &year);
        printf("You entered the date %.4d%.2d%.2d\n\n", year, month, day);
    }
}
