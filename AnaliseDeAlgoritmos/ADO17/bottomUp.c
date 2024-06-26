#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

void MatrixChainOrder(int p[], int n)
{
    int m[n][n];
    int i, j, k, L, q;

    for (i=1; i<n; i++)
        m[i][i] = 0;

    for (L=2; L<n; L++)
    {
        for (i=1; i<n-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INT_MAX;
            for (k=i; k<=j-1; k++)
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    printf("O menor numero de multiplicacoes: %d ", m[1][n-1]);
}

int main()
{
    int arr[] = {1, 2, 3, 4, 3};
    int size = sizeof(arr)/sizeof(arr[0]);

    MatrixChainOrder(arr, size);

    return 0;
}
