// decimal to octal

#include <stdio.h>

int main() {
    while (1) {
        printf("Enter a number between 0 and 32767: ");
        int input_num = 0;
        scanf("%d", &input_num);
        
        int octal_digits[5];
        for (int i = 4; i >= 0; i--) {
            octal_digits[i] = input_num % 8;
            input_num /= 8;
        }

        printf("In octal, your number is: ");
        for (int i = 0; i <= 4; i++) {
            printf("%d", octal_digits[i]);
        }
        printf("\n\n");
    }
}
