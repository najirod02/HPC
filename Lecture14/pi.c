#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * a simple program that computes the pi value given a 
 * number of iterations and the number of threads to run
 * 
 * we use also the guided schedule option for the for loop
 */

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);
    int thread_count = strtol(argv[2], NULL, 10);
    double sum = 0.0, factor = 0.0;
    int k = 0;

    #pragma omp parallel for num_threads(thread_count) reduction(+:sum) private(factor) \
    schedule(guided)
    for(k=0; k<n; k++){
        if(k%2 == 0)
            factor = 1.0;
        else
            factor = -1.0;
        
        sum += factor/(2*k+1);
    }

    double res = 4.0*sum;
    printf("Pi for %d iterations: %f\n", n, res);
    return 0;
}
