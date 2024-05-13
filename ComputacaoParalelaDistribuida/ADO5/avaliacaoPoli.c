#include <stdio.h>
#include <omp.h>

double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double evaluate_polynomial(double coefficients[], int degree, double x) {
    if (degree == 0) {
        return coefficients[0];
    } else {
        double lower_half = evaluate_polynomial(coefficients, degree / 2, x);
        double higher_half = evaluate_polynomial(coefficients + (degree / 2) + 1, degree - (degree / 2) - 1, x);
        double x_power = power(x, degree / 2);
        return lower_half + x_power * higher_half;
    }
}

int main() {
    int degree = 3;
    double coefficients[] = {2.0, -3.0, 1.0, 4.0}; 

    double x = 2.0;

    double result = evaluate_polynomial(coefficients, degree, x);
    printf("Resultado do polinômio para x = %.2lf: %.2lf\n", x, result);

    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        double res = evaluate_polynomial(coefficients, degree, x);
        printf("Thread %d: Resultado = %.2lf\n", omp_get_thread_num(), res);
    }

    return 0;
}
