
#include <cuda.h>

__global__
void doNothing() {
    // does nothing... somewhat anticlimatic
}

int main(int argc, char *argv[]) {
    printf("hello world!\n");
    doNothing<<<1,1>>>();
    return 0;
}
