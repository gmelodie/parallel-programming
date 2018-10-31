// Sums 2 integers and stores on a third integer (sums on the GPU)
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>


__global__ void add(int *d_a, int *d_b, int *d_c) {
    *d_c = *d_a + *d_b;
}


int main(int argc, char *argv[]) {
    int a = 2, b = 3, c;
    int *d_a, *d_b, *d_c;

    // allocate memory on device
    cudaMalloc((void **) &d_a, sizeof(int));
    cudaMalloc((void **) &d_b, sizeof(int));
    cudaMalloc((void **) &d_c, sizeof(int));

    // Put data on device (GPU)
    cudaMemcpy(d_a, &a, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &b, sizeof(int), cudaMemcpyHostToDevice);

    // calculate sum
    sum<<<1,1>>>(d_a, d_b, d_c);

    // Put result on host variable
    cudaMemcpy(&c, d_c, sizeof(int), cudaMemcpyDeviceToHost);

    printf("%d\n", c);


    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}
