#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("Hello from the serial world\n");
    const char* omp_threads_env = getenv("OMP_NUM_THREADS");
    int num_threads = 10;//default in case the env variable is not set
    if (omp_threads_env != NULL) {
        num_threads = atoi(omp_threads_env);
    }

    #pragma omp parallel num_threads(num_threads)
    {
        printf("Hello world... from thread = %d\n", omp_get_thread_num());
    }

    printf("Back to the serial world\n");
    return 0;
}
