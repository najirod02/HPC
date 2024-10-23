#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

/**
 a program that takes data from process zero and sends it to all of the pìother processes
 by sending it in a ring. That is, process i should receive the data and send it oto process i+1,
 until the last process is reached.
 */

int main(int argc, char** argv){
    char greeting[MAX_STRING];
    int comm_sz; //number of processes
    int my_rank; //my process rank

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank != 0){
        //simply wait the i-1 process messagge and then forward it to the i+1.
        //if last one, simply print and end
        MPI_Recv(greeting, MAX_STRING, MPI_CHAR, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received: %s\n", my_rank, greeting);

        if(my_rank <= (comm_sz - 1)){
            sprintf(greeting, "Sending from process %d to %d!", my_rank, my_rank+1);
            MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, my_rank+1, 0, MPI_COMM_WORLD);
        }
    }else{
        //'main' process
        //Send it to the first child!
        printf("Process 0 started\n");
        if(comm_sz > 1){
            sprintf(greeting, "Sending from process %d to %d!", my_rank, my_rank+1);
            MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, my_rank+1, 0, MPI_COMM_WORLD);
        } else {
            printf("No child process to forward\n");
        }
    }

    MPI_Finalize();
    return 0;
}