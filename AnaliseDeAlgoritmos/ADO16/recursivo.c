#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapSackRec(int W, int wt[], int val[], int n, int** memo) {
    if (n == 0 || W == 0)
        return 0;

    if (memo[n][W] != -1)
        return memo[n][W];

    if (wt[n-1] > W)
        memo[n][W] = knapSackRec(W, wt, val, n-1, memo);
    else
        memo[n][W] = max(val[n-1] + knapSackRec(W - wt[n-1], wt, val, n-1, memo),
                         knapSackRec(W, wt, val, n-1, memo));

    return memo[n][W];
}

int knapSack(int W, int wt[], int val[], int n) {
    int** memo = (int**)malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        memo[i] = (int*)malloc((W+1) * sizeof(int));
        for (int j = 0; j <= W; j++)
            memo[i][j] = -1;
    }

    int result = knapSackRec(W, wt, val, n, memo);

    for (int i = 0; i <= n; i++)
        free(memo[i]);
    free(memo);

    return result;
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val)/sizeof(val[0]);

    printf("Valor maximo que pode ser colocado na mochila: %d\n", knapSack(W, wt, val, n));

    return 0;
}
