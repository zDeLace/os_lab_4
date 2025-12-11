#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contracts.h"

/* Типы функций */
typedef int (*pf_PrimeCount)(int,int);
typedef float (*pf_Pi)(int);

/* helper to load library and fetch function pointers */
struct Lib {
    void *handle;
    pf_PrimeCount primecount;
    pf_Pi pi;
    char path[256];
};

int load_lib(struct Lib *lib, const char *path) {
    if (lib->handle) {
        dlclose(lib->handle);
        lib->handle = NULL;
        lib->primecount = NULL;
        lib->pi = NULL;
    }
    void *h = dlopen(path, RTLD_NOW);
    if (!h) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return -1;
    }
    pf_PrimeCount pc = (pf_PrimeCount)dlsym(h, "PrimeCount");
    char *err = dlerror();
    if (err) { fprintf(stderr,"dlsym PrimeCount: %s\n", err); dlclose(h); return -1; }
    pf_Pi pif = (pf_Pi)dlsym(h, "Pi");
    err = dlerror();
    if (err) { fprintf(stderr,"dlsym Pi: %s\n", err); dlclose(h); return -1; }
    lib->handle = h;
    lib->primecount = pc;
    lib->pi = pif;
    strncpy(lib->path, path, sizeof(lib->path)-1);
    lib->path[sizeof(lib->path)-1] = 0;
    return 0;
}

int main(void) {
    struct Lib lib = {0};
    /* по умолчанию первая реализация */
    const char *lib1 = "./libimpl_naive.so";
    const char *lib2 = "./libimpl_fast.so";
    if (load_lib(&lib, lib1) != 0) {
        fprintf(stderr, "Failed to load default library %s\n", lib1);
        return 1;
    }
    printf("Program DYNAMIC. Loaded: %s\n", lib.path);
    printf("Commands:\n0 -> switch implementation\n1 A B -> PrimeCount(A,B)\n2 K -> Pi(K)\nq -> exit\n");
    char line[256];
    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        if (line[0] == 'q') break;
        if (line[0] == '0') {
            const char *to = (strcmp(lib.path, lib1) == 0) ? lib2 : lib1;
            if (load_lib(&lib, to) == 0) {
                printf("Switched to %s\n", lib.path);
            } else {
                printf("Switch failed\n");
            }
        } else if (line[0] == '1') {
            int A,B;
            if (sscanf(line+1, "%d %d", &A, &B) == 2) {
                int res = lib.primecount(A,B);
                printf("PrimeCount(%d,%d) = %d\n", A,B,res);
            } else {
                printf("Invalid args for 1\n");
            }
        } else if (line[0] == '2') {
            int K;
            if (sscanf(line+1, "%d", &K) == 1) {
                float p = lib.pi(K);
                printf("Pi(%d) = %.10f\n", K, p);
            } else {
                printf("Invalid args for 2\n");
            }
        } else {
            printf("Unknown command\n");
        }
    }
    if (lib.handle) dlclose(lib.handle);
    return 0;
}
