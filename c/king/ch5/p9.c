// date comparator

#include <stdio.h>
#include <stdbool.h>

int main() {
    while (1) {
        printf("Enter first date (mm/dd/yy): ");
        int month_1, day_1, year_1;
        scanf("%d/%d/%d", &month_1, &day_1, &year_1);

        printf("Enter second date (mm/dd/yy): ");
        int month_2, day_2, year_2;
        scanf("%d/%d/%d", &month_2, &day_2, &year_2);

        bool is_date1_earlier = (year_1 < year_2);
        if (year_1 == year_2) {
            is_date1_earlier = (month_1 < month_2);
            if (month_1 == month_2) {
                is_date1_earlier = (day_1 < day_2);
            }
        }

        if (is_date1_earlier) {
            printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n\n", month_1, day_1, year_1,
                month_2, day_2, year_2);
        } else {
            printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n\n", month_2, day_2, year_2,
                month_1, day_1, year_1);
        }
    }
}
