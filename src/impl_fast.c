#include "contracts.h"
#include <stdlib.h>
#include <math.h>

/* Решето Эратосфена */
int PrimeCount(int A, int B) {
    if (A > B) { int t=A; A=B; B=t; }
    if (B < 2) return 0;
    if (A < 2) A = 2;
    int n = B;
    char *is_prime = (char*)malloc(n + 1);
    if (!is_prime) return 0;
    for (int i = 0; i <= n; ++i) is_prime[i] = 1;
    is_prime[0] = is_prime[1] = 0;
    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int q = p * p; q <= n; q += p) is_prime[q] = 0;
        }
    }
    int count = 0;
    for (int i = A; i <= B; ++i) if (is_prime[i]) ++count;
    free(is_prime);
    return count;
}

/* Формула Валлиса:
   pi/2 = product_{k=1..K} (4 k^2) / (4 k^2 - 1)
   => pi = 2 * product(...)
   (используем K > 0; при больших K product близок к pi/2)
*/
float Pi(int K) {
    if (K <= 0) return 0.0f;
    double prod = 1.0;
    for (int k = 1; k <= K; ++k) {
        double num = 4.0 * k * k;
        double den = num - 1.0;
        prod *= num / den;
    }
    return (float)(2.0 * prod);
}
