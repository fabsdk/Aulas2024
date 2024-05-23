#include<stdio.h>
#include<string.h>

#define MAX 1000

int dp[MAX][MAX];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs(char *X, char *Y, int m, int n) {
    int i, j;
    for(i=0; i<=m; i++) {
        for(j=0; j<=n; j++) {
            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if(X[i-1] == Y[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);
    printf("O comprimento de LCS:%d\n", lcs(X, Y, m, n));
    return 0;
}
