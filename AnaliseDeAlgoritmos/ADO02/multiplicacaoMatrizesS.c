#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int **allocateMatrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void matrixAdd(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrixSubtract(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void splitMatrix(int **parent, int **child, int row, int col, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            child[i][j] = parent[row + i][col + j];
        }
    }
}

void mergeMatrix(int **child, int **parent, int row, int col, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            parent[row + i][col + j] = child[i][j];
        }
    }
}

void strassenMultiply(int **A, int **B, int **C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize);
    int **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize);
    int **C22 = allocateMatrix(newSize);

    splitMatrix(A, A11, 0, 0, newSize);
    splitMatrix(A, A12, 0, newSize, newSize);
    splitMatrix(A, A21, newSize, 0, newSize);
    splitMatrix(A, A22, newSize, newSize, newSize);
    splitMatrix(B, B11, 0, 0, newSize);
    splitMatrix(B, B12, 0, newSize, newSize);
    splitMatrix(B, B21, newSize, 0, newSize);
    splitMatrix(B, B22, newSize, newSize, newSize);

    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize);
    int **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize);
    int **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);

    int **temp1 = allocateMatrix(newSize);
    int **temp2 = allocateMatrix(newSize);

    matrixAdd(A11, A22, temp1, newSize);
    matrixAdd(B11, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, M1, newSize);

    matrixAdd(A21, A22, temp1, newSize);
    strassenMultiply(temp1, B11, M2, newSize);

    matrixSubtract(B12, B22, temp1, newSize);
    strassenMultiply(A11, temp1, M3, newSize);

    matrixSubtract(B21, B11, temp1, newSize);
    strassenMultiply(A22, temp1, M4, newSize);

    matrixAdd(A11, A12, temp1, newSize);
    strassenMultiply(temp1, B22, M5, newSize);

    matrixSubtract(A21, A11, temp1, newSize);
    matrixAdd(B11, B12, temp2, newSize);
    strassenMultiply(temp1, temp2, M6, newSize);

    matrixSubtract(A12, A22, temp1, newSize);
    matrixAdd(B21, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, M7, newSize);

    int **temp3 = allocateMatrix(newSize);
    int **temp4 = allocateMatrix(newSize);

    matrixAdd(M1, M4, temp1, newSize);
    matrixSubtract(temp1, M5, temp2, newSize);
    matrixAdd(temp2, M7, C11, newSize);

    matrixAdd(M3, M5, C12, newSize);

    matrixAdd(M2, M4, C21, newSize);

    matrixAdd(M1, M3, temp1, newSize);
    matrixSubtract(temp1, M2, temp2, newSize);
    matrixAdd(temp2, M6, C22, newSize);

    mergeMatrix(C11, C, 0, 0, newSize);
    mergeMatrix(C12, C, 0, newSize, newSize);
    mergeMatrix(C21, C, newSize, 0, newSize);
    mergeMatrix(C22, C, newSize, newSize, newSize);

    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);
    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);
    freeMatrix(C11, newSize);
    freeMatrix(C12, newSize);
    freeMatrix(C21, newSize);
    freeMatrix(C22, newSize);
    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);
    freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);
    freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(temp1, newSize);
    freeMatrix(temp2, newSize);
    freeMatrix(temp3, newSize);
    freeMatrix(temp4, newSize);
}

int main() {
    int n;
    printf("Digite a ordem das matrizes quadradas: ");
    scanf("%d", &n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("Digite os elementos da matriz A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Digite os elementos da matriz B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    strassenMultiply(A, B, C, n);

    printf("Matriz resultante C:\n");
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
