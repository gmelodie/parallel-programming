#include <omp.h>
#include <stdio.h>
#include <limits.h>

int main() {
    int sum;

    #pragma omp parallel num_threads(4)
    {
        #pragma omp barrier // comment this line
        printf("yello\n");

        #pragma omp barrier // comment this line
        printf("I'm\n");

        #pragma omp barrier // comment this line
        printf("back\n");
    }
    return 0;
}
