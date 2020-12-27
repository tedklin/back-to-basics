// magic square

#include <stdio.h>

int main() {
    while (1) {
        int arr[16];
        printf("Enter the numbers 1 through 16 in any order:\n");
        for (int i = 0; i != 16; i++) {
            scanf("%d", arr + i);
        }

        printf("\nSquare form:\n");
        for (int i = 0; i != 16; i++) {
            printf("%2d ", arr[i]);
            if (i % 4 == 3) {
                printf("\n");
            }
        }

        printf("\nRow sums:");
        for (int row = 0; row != 4; row++) {
            int row_sum = 0;
            for (int col = 0; col != 4; col++) {
                row_sum += arr[row * 4 + col];
            }
            printf("%3d", row_sum);
        }

        printf("\nColumn sums:");
        for (int col = 0; col != 4; col++) {
            int col_sum = 0;
            for (int row = 0; row != 4; row++) {
                col_sum += arr[row * 4 + col];
            }
            printf("%3d", col_sum);
        }

        printf("\nDiagonal sums:");
        int diagonal_1_sum = 0, diagonal_2_sum = 0;
        for (int i = 0; i != 4; i++) {
            diagonal_1_sum += arr[i * 4 + i];
            diagonal_2_sum += arr[i * 4 + (3 - i)];
        }
        printf("%3d%3d\n\n", diagonal_1_sum, diagonal_2_sum);
    }
}
