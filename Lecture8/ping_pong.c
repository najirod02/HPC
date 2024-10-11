#include <stdio.h>
#include <string.h>
#include <mpi.h>

/*
Implement a “ping pong” using send & receive
Two processes one send and one receive each
*/

const int DIM_BUFFER = 100;

int main(int argc, char** argv){
    char message[DIM_BUFFER];
    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank == 0){
        //the main process sends the message and waits the response
        sprintf(message, "Message from %d to process %d", my_rank, my_rank+1);
        MPI_Send(message, strlen(message)+1, MPI_CHAR, my_rank+1, 0, MPI_COMM_WORLD);

        //wait for response
        MPI_Recv(message, DIM_BUFFER, MPI_CHAR, my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("MESSAGE RECEIVED:\t%s\n", message);
    } else{
        //wait for main process message and then respond
        MPI_Recv(message, DIM_BUFFER, MPI_CHAR, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("MESSAGE RECEIVED:\t%s\n", message);

        sprintf(message, "Message from %d to process %d", my_rank, my_rank-1);
        MPI_Send(message, strlen(message)+1, MPI_CHAR, my_rank-1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}