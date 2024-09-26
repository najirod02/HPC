#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

/**
 * a simple program where the 'main' process waits to receive a message from all other processes.
 * In this case, we wait sequentially to receive a message.
 * 
 * We could also receive a message without knowing the sender using MPI_ANY_SOURCE making a 
 * more 'parallel' execution
 */

int main(int argc, char** argv){
    char greeting[MAX_STRING];
    int comm_sz; //number of processes
    int my_rank; //my process rank

    MPI_Init(NULL, NULL);//from here is like we run multiple times the same code on different processes
    //note that every variable is duplicated and is located in its own memory location of the process

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank != 0){
        //'child' process
        sprintf(greeting, "Greetings from  process %d of %d!", my_rank, comm_sz);
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }else{
        //'main' process
        printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
        for(int q=1; q<comm_sz; q++){
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //MPI_Recv(greeting, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    }

    MPI_Finalize();
    return 0;
}