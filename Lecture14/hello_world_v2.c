#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * the difference from the first version is that now it is possible
 * to specify the number of threads you want to run
 */

void Hello(void); //thread function

int main(int argc, char const *argv[])
{
    int thread_count = strtol(argv[1], NULL, 10);

    #pragma omp parallel num_threads(thread_count)
    Hello();

    return 0;
}

void Hello(void){
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    printf("Hello from thread %d of %d\n", my_rank, thread_count);
}