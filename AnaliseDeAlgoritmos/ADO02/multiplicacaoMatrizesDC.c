#include <stdio.h>

void multiplyMatrix(int A[][2], int B[][2], int C[][2], int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int i, j;
    int A11[2][2], A12[2][2], A21[2][2], A22[2][2];
    int B11[2][2], B12[2][2], B21[2][2], B22[2][2];
    int C11[2][2], C12[2][2], C21[2][2], C22[2][2];
    int P1[2][2], P2[2][2], P3[2][2], P4[2][2], P5[2][2], P6[2][2], P7[2][2];

    // Dividindo as matrizes em submatrizes
    for (i = 0; i < n/2; i++) {
        for (j = 0; j < n/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+n/2];
            A21[i][j] = A[i+n/2][j];
            A22[i][j] = A[i+n/2][j+n/2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+n/2];
            B21[i][j] = B[i+n/2][j];
            B22[i][j] = B[i+n/2][j+n/2];
        }
    }

    // Calculando os produtos intermediários
    multiplyMatrix(A11, B11, P1, n/2);
    multiplyMatrix(A12, B21, P2, n/2);
    multiplyMatrix(A11, B12, P3, n/2);
    multiplyMatrix(A12, B22, P4, n/2);
    multiplyMatrix(A21, B11, P5, n/2);
    multiplyMatrix(A22, B21, P6, n/2);
    multiplyMatrix(A21, B12, P7, n/2);

    // Calculando as submatrizes do resultado
    for (i = 0; i < n/2; i++) {
        for (j = 0; j < n/2; j++) {
            C11[i][j] = P1[i][j] + P2[i][j];
            C12[i][j] = P3[i][j] + P4[i][j];
            C21[i][j] = P5[i][j] + P6[i][j];
            C22[i][j] = P1[i][j] - P3[i][j] + P5[i][j] + P7[i][j];
        }
    }

    // Combinando as submatrizes para obter a matriz resultante
    for (i = 0; i < n/2; i++) {
        for (j = 0; j < n/2; j++) {
            C[i][j] = C11[i][j];
            C[i][j+n/2] = C12[i][j];
            C[i+n/2][j] = C21[i][j];
            C[i+n/2][j+n/2] = C22[i][j];
        }
    }
}

void displayMatrix(int matrix[][2], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[][2] = {{1, 2}, {3, 4}};
    int B[][2] = {{5, 6}, {7, 8}};
    int C[2][2];

    multiplyMatrix(A, B, C, 2);

    printf("Matrix A:\n");
    displayMatrix(A, 2);
    printf("Matrix B:\n");
    displayMatrix(B, 2);
    printf("Result Matrix C:\n");
    displayMatrix(C, 2);

    return 0;
}
