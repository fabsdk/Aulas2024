#include <stdio.h>
#include <limits.h>

int minCoinsBottomUp(int coins[], int m, int V) {
    int dp[V + 1];

    // Inicializar dp com valor máximo
    for (int i = 0; i <= V; i++) dp[i] = INT_MAX;

    dp[0] = 0;  // Caso base

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < m; j++) {
            if (coins[j] <= i) {
                int sub_res = dp[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }

    return dp[V];
}

int main() {
    int coins[] = {1, 3, 4};
    int m = sizeof(coins) / sizeof(coins[0]);
    int V = 6;

    int result = minCoinsBottomUp(coins, m, V);

    if (result == INT_MAX) {
        printf("Nao e possivel fazer o troco\n");
    } else {
        printf("Numero minimo de moedas necessarias: %d\n", result);
    }

    return 0;
}
