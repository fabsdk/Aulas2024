#include <stdio.h>
#include <limits.h>

#define MAX 1000

int minCoinsTopDown(int coins[], int m, int V, int dp[]) {
    // Caso base
    if (V == 0) return 0;
    if (dp[V] != -1) return dp[V];

    int res = INT_MAX;

    for (int i = 0; i < m; i++) {
        if (coins[i] <= V) {
            int sub_res = minCoinsTopDown(coins, m, V - coins[i], dp);
            if (sub_res != INT_MAX && sub_res + 1 < res) {
                res = sub_res + 1;
            }
        }
    }

    dp[V] = res;
    return res;
}

int main() {
    int coins[] = {1, 3, 4};
    int m = sizeof(coins) / sizeof(coins[0]);
    int V = 6;
    int dp[MAX];

    for (int i = 0; i <= V; i++) dp[i] = -1;

    int result = minCoinsTopDown(coins, m, V, dp);

    if (result == INT_MAX) {
        printf("Nao e possível fazer o troco\n");
    } else {
        printf("Numero minimo de moedas necessarias: %d\n", result);
    }

    return 0;
}
