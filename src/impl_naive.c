#include "contracts.h"
#include <math.h>
#include <stdlib.h>

/* Проверка простоты: наивный, деление на все предыдущие числа (2..n-1) */
static int is_prime_naive(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    for (int d = 2; d <= n-1; ++d) {
        if (n % d == 0) return 0;
    }
    return 1;
}

int PrimeCount(int A, int B) {
    if (A > B) { int t = A; A = B; B = t; }
    if (B < 2) return 0;
    if (A < 2) A = 2;
    int count = 0;
    for (int i = A; i <= B; ++i) {
        if (is_prime_naive(i)) ++count;
    }
    return count;
}

/* Pi: ряд Лейбница: pi = 4 * sum_{k=0..K-1} (-1)^k / (2k+1) */
float Pi(int K) {
    if (K <= 0) return 0.0f;
    double sum = 0.0;
    for (int k = 0; k < K; ++k) {
        double term = (k % 2 == 0 ? 1.0 : -1.0) / (2.0 * k + 1.0);
        sum += term;
    }
    return (float)(4.0 * sum);
}
