#include <omp.h>
#include <stdio.h>
#include <limits.h>


#define N 1000
#define CHUNKSIZE 100

int main() {
    int a[N], b[N], c[N], chunk = CHUNKSIZE;
    int i, j, k;

    #pragma omp parallel shared(a, b, c, chunk) private(i, j, k)
    {
//        #pragma omp for schedule(static, chunk) nowait
        for(i = 0; i < N; i++) {
            a[i] = i;
        }

//        #pragma omp for schedule(static, chunk) nowait
        for(j = 0; j < N; j++) {
            b[j] = N-j;
        }

//        #pragma omp for schedule(static, chunk) nowait
        for(k = 0; k < N; k++) {
            c[k] = b[k] + a[k];
        }
    }

    return 0;
}
