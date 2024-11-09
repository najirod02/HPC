#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("Hello from the serial world\n");

    #pragma omp parallel num_threads(10)
    {
        printf("Hello world... from thread = %d\n", omp_get_thread_num());
    }

    printf("Back to the serial world\n");
    return 0;
}
