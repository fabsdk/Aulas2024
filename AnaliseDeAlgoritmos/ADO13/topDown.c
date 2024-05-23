#include <stdio.h>

#define MAX 1000

int memo[MAX];

int fibonacci_top_down(int n) {
    if (n <= 1) {
        return n;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    memo[n] = fibonacci_top_down(n - 1) + fibonacci_top_down(n - 2);
    return memo[n];
}

int main() {
    int n;

    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    for (int i = 0; i < MAX; i++) {
        memo[i] = -1;
    }

    int result = fibonacci_top_down(n);
    printf("Fibonacci de %d e %d\n", n, result);

    return 0;
}
