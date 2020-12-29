// gcd

#include <stdio.h>

int main() {
    printf("Enter two integers: ");
    int m, n;
    scanf("%d %d", &m, &n);

    while (n != 0) {
        int remainder = m % n;
        m = n;
        n = remainder;
    }

    printf("GCD: %d\n", m);
}
