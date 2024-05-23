#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

int MatrixChainOrder(int p[], int i, int j, int **m)
{
    if(i == j)
        return 0;
    if(m[i][j] != -1)
        return m[i][j];
    m[i][j] = INT_MAX;
    for (int k=i; k<j; k++)
    {
        int count = MatrixChainOrder(p, i, k, m) + MatrixChainOrder(p, k+1, j, m) + p[i-1]*p[k]*p[j];
        if (count < m[i][j])
            m[i][j] = count;
    }
    return m[i][j];
}

int main()
{
    int arr[] = {1, 2, 3, 4, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    int **m = (int **)malloc(n * sizeof(int *));
    for(int i=0; i<n; i++)
        m[i] = (int *)malloc(n * sizeof(int));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            m[i][j] = -1;

    printf("O menor numero de multiplicacoes: %d ", MatrixChainOrder(arr, 1, n-1, m));

    return 0;
}
