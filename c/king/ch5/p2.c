// 24-hr time

#include <stdio.h>
#include <stdbool.h>

int main() {
    while (1) {
        printf("Enter a 24-hr time: ");
        int hour, minute;
        scanf("%d:%d", &hour, &minute);

        bool is_am = true;
        if (hour >= 12) {
            is_am = false;
            if (hour != 12) {
                hour %= 12;
            }
        }
        if (hour == 0) {
            hour = 12;
        }

        printf("Equivalent 12-hr time: %d:%.2d", hour, minute);
        if (is_am) {
            printf(" AM\n\n");
        } else {
            printf(" PM\n\n");
        }
    }
}
