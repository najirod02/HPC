#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>

const int DIM_BUFFER = 100;
const int STR_BUFFER = 200;

/**
 * given a vector, the main process scatters it 
 * to the different processes.
 * if the number of processes if odd, a part of the vector will
 * be lost
 */
int main(int argc, char** argv) {
    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int *vector = NULL;
    int *recv_buff = NULL;
    int elements_per_proc = DIM_BUFFER / comm_sz;

    //each process will receive 'elements_per_proc' elements
    recv_buff = malloc(sizeof(int) * elements_per_proc);
    char message[STR_BUFFER];

    if (my_rank == 0) {
        vector = malloc(sizeof(int) * DIM_BUFFER);
        for (int i = 0; i < DIM_BUFFER; i++) {
            vector[i] = i + 1;
        }
    }

    //distribute the vector
    MPI_Scatter(vector, elements_per_proc, MPI_INT, recv_buff, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    //create the message with sprintf
    sprintf(message, "Proces %d has received:", my_rank);
    for (int i = 0; i < elements_per_proc; i++) {
        char buffer[20];
        sprintf(buffer, " %d", recv_buff[i]);
        strcat(message, buffer);
    }
    strcat(message, "\n");

    printf("%s", message);

    free(recv_buff);
    if (my_rank == 0) {
        free(vector);
    }

    MPI_Finalize();
    return 0;
}
