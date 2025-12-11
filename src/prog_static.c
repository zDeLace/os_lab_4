#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contracts.h"

/* Простейший CLI:
   "1 A B" -> вызывает PrimeCount(A,B)
   "2 K"   -> вызывает Pi(K)
   "q"     -> выход
*/
int main(void) {
    char cmd[256];
    printf("Program STATIC (linked at compile time). Commands:\n");
    printf("1 A B -> PrimeCount(A,B)\n2 K -> Pi(K)\nq -> exit\n");
    while (1) {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        if (cmd[0] == 'q') break;
        if (cmd[0] == '1') {
            int A, B;
            if (sscanf(cmd+1, "%d %d", &A, &B) == 2) {
                int res = PrimeCount(A,B);
                printf("PrimeCount(%d,%d) = %d\n", A, B, res);
            } else {
                printf("Invalid args for 1\n");
            }
        } else if (cmd[0] == '2') {
            int K;
            if (sscanf(cmd+1, "%d", &K) == 1) {
                float p = Pi(K);
                printf("Pi(%d) = %.10f\n", K, p);
            } else {
                printf("Invalid args for 2\n");
            }
        } else {
            printf("Unknown command\n");
        }
    }
    return 0;
}
