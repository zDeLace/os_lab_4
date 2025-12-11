#ifndef CONTRACTS_H
#define CONTRACTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Возвращает число простых чисел на отрезке [A,B] (A,B - натуральные) */
int PrimeCount(int A, int B);

/* Вычисление числа Pi по длине ряда K (K > 0) */
float Pi(int K);

#ifdef __cplusplus
}
#endif

#endif // CONTRACTS_H