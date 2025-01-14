#include <stdio.h>

void matvecmul(int m, int n, double A[m][n], double b[n], double result[m]) {
    for (int i = 0; i < m; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * b[j];
        }
    }
}

int main() {
    int m = 2, n = 3;
    double A[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double b[3] = {1, 2, 3};
    double result[2];

    matvecmul(m, n, A, b, result);

    printf("Result vector:\n");
    for (int i = 0; i < m; i++) {
        printf("%f\n", result[i]);
    }

    return 0;
}