#include<stdio.h>
#include<string.h>

#define MAX 1000

int dp[MAX][MAX];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs(char *X, char *Y, int m, int n) {
    if(m == 0 || n == 0)
        return 0;
    if(dp[m-1][n-1] != -1)
        return dp[m-1][n-1];
    if(X[m-1] == Y[n-1])
        return dp[m-1][n-1] = 1 + lcs(X, Y, m-1, n-1);
    else
        return dp[m-1][n-1] = max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n));
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);
    memset(dp, -1, sizeof(dp));
    printf("O comprimento de LCS: %d\n", lcs(X, Y, m, n));
    return 0;
}
