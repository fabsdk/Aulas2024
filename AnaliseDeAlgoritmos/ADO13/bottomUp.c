#include <stdio.h>

int fibonacci_bottom_up(int n) {
    if (n <= 1) {
        return n;
    }

    int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main() {
   int n;

    printf("Digite um numero inteiro: ");
    scanf("%d", &n);
    int result = fibonacci_bottom_up(n);
    printf("Fibonacci de %d e %d\n", n, result);

    return 0;
}
