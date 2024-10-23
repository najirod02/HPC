#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 6
#define COLS 5
#define DIM (ROWS * COLS)

/**
 * given a matrix and a vector,
 * compute the product.
 * 
 * at the end, the time taken will be printed
 */
int main(int argc, char** argv) {
    //a 6x5 matrix
    const int matrix[DIM] = {1, 2, 3, 4, 5,
                            6, 7, 8, 9, 10,
                            11, 12, 13, 14, 15,
                            16, 17, 18, 19, 20,
                            21, 22, 23, 24, 25,
                            26, 27, 28, 29, 30
                        };

    int x[COLS] = {1, 2, 3, 4, 5};

    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //each process, will take ROWS/comm_size rows from the matrix
    int n_rows = ROWS/comm_sz;
    int* recv_buff = malloc((n_rows*COLS)*sizeof(int));

    //distribute the elements to each process (also 0 !!)
    clock_t time = clock();
    MPI_Scatter(matrix, n_rows * COLS, MPI_INT, recv_buff, n_rows * COLS, MPI_INT, 0, MPI_COMM_WORLD);

    //now each process has its own elements 
    int* local_result = calloc(n_rows, sizeof(int));;

    for(int i=0; i<n_rows; i++){
        for(int j=0; j<COLS; j++){
            local_result[i] += recv_buff[COLS*i + j] * x[j];
        }
    }
    free(recv_buff);

    //gather all results
    int *gathered_result = NULL;
    if(my_rank == 0) gathered_result = calloc(ROWS, sizeof(int));

    MPI_Gather(local_result, n_rows, MPI_INT, gathered_result, n_rows, MPI_INT, 0, MPI_COMM_WORLD);

    /*
    it is possible to distribute the gathered results to all process by calling
    MPI_Allgather. Note also that in this case, you must allocate for each process the
    gathered_result vector!
    */

    if(my_rank == 0){
        for(int i=0; i<ROWS; i++){
            printf("%d\t", gathered_result[i]);
        }
        printf("\n");
        time = clock() - time;
        printf("Time taken %f\n", (double)time/CLOCKS_PER_SEC);
        free(gathered_result);
    }

    free(local_result);

    MPI_Finalize();
    return 0;
}