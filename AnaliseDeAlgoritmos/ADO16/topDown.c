#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int knapsackTopDown(int W, int wt[], int val[], int n, int **dp) {
    if (n == 0 || W == 0) {
        return 0;
    }

    if (dp[n][W] != -1) {
        return dp[n][W];
    }

    if (wt[n-1] > W) {
        dp[n][W] = knapsackTopDown(W, wt, val, n-1, dp);
    } else {
        dp[n][W] = MAX(
            val[n-1] + knapsackTopDown(W - wt[n-1], wt, val, n-1, dp),
            knapsackTopDown(W, wt, val, n-1, dp)
        );
    }

    return dp[n][W];
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
        for (int j = 0; j <= W; j++) {
            dp[i][j] = -1;
        }
    }

    printf("Valor maximo na mochila top-down = %d\n", knapsackTopDown(W, wt, val, n, dp));

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}
