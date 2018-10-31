// Sums 2 integer vectors and stores on a third vector (sums on the GPU)
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N 512


__global__ void add(int *d_a, int *d_b, int *d_c) {
    d_c[blockIdx.x] = d_a[blockIdx.x] + d_b[blockIdx.x];
}


void random_ints(int *vec, int n) {
    for (int i = 0; i < n; i++)
        vec[i] = rand();
}


int main(int argc, char *argv[]) {
    int size = N * sizeof(int);
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;

    // allocate memory on device
    cudaMalloc((void **) &d_a, size);
    cudaMalloc((void **) &d_b, size);
    cudaMalloc((void **) &d_c, size);

    // initialize inputs on host
    srand(time(NULL));
    a = malloc(size);
    random_ints(a, N);
    b = malloc(size);
    random_ints(b, N);
    c = malloc(size);

    // Put data on device (GPU)
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    // calculate sum
    sum<<<size,1>>>(d_a, d_b, d_c);
    //kernel<<<blocks, threads>>>();

    // Put result on host variable
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("%d\n", c);

    free(a);
    free(b);
    free(c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}
