// approximating e

#include <stdio.h>

int main() {
    printf("Enter number of terms: ");
    int n;
    scanf("%d", &n);

    double e = 1;
    for (int i = 1; i <= n; i++) {
        e += (1.0 / factorial(i));
    }

    printf("e approximated to %d terms = %.20f\n", n, e);
}

int factorial(int i) {
    int result = 1;
    while (i > 1) {
        result *= i;
        i--;
    }
    return result;
}
