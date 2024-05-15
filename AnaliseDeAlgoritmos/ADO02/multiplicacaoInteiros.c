#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int tamanhoNumero(int num) {
    int tamanho = 0;
    while (num != 0) {
        num /= 10;
        tamanho++;
    }
    return tamanho;
}

int multiplicacaoKaratsuba(int x, int y) {
    int tamanhoX = tamanhoNumero(x);
    int tamanhoY = tamanhoNumero(y);
    int n = fmax(tamanhoX, tamanhoY);
    
    // Caso base para a recursão
    if (n == 1) {
        return x * y;
    }

    int metade = n / 2;

    int a = x / (int)pow(10, metade);
    int b = x % (int)pow(10, metade);
    int c = y / (int)pow(10, metade);
    int d = y % (int)pow(10, metade);

    int ac = multiplicacaoKaratsuba(a, c);
    int bd = multiplicacaoKaratsuba(b, d);
    int ad_bc = multiplicacaoKaratsuba(a+b, c+d) - ac - bd;

    int resultado = ac * (int)pow(10, 2*metade) + ad_bc * (int)pow(10, metade) + bd;

    return resultado;
}

int main() {
    int x = 1234;
    int y = 5678;

    int resultado = multiplicacaoKaratsuba(x, y);
    printf("O resultado da multiplicacao de %d e %d eh: %d\n", x, y, resultado);

    return 0;
}
