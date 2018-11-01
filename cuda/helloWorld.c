#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void doNothing(void) {
    // does nothing... somewhat anticlimatic
    return;
}

int main(int argc, char *argv[]) {
    doNothing<<<1,1>>>();
    printf("hello world!\n");
    return 0;
}
