#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

/**
 a process 'p' wants to share the content of a variable 'a'
 with all the other processes.

 Note that a broadcast comunication already exists: MPI_Bcast
 */

int main(int argc, char** argv){
    char greeting[MAX_STRING];
    int comm_sz; //number of processes
    int my_rank; //my process rank
    int p = 0; //sender rank

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //get the sender rank (if valid)
    if (argc >=2){
        p = atoi(argv[1]);
        if(p < 0 || p >= comm_sz){
            if(my_rank == 0)
                printf("Non valid sender rank. Needs to be in range 0 - %d\n", comm_sz-1);
            MPI_Finalize();
            return 0;
        }
    } else {
        if(my_rank == 0)
            printf("Please, indicate which process is the sender\nmpiexec -n <x> <exec> <sender_rank>\n");
        MPI_Finalize();
        return 0;
    }

    if(my_rank != p){
        //i am the receiver of the broadcast message
        MPI_Status status;
        MPI_Recv(greeting, MAX_STRING, MPI_CHAR, p, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received: %s (error code: %d)\n", my_rank, greeting, status.MPI_ERROR);
    }else{
        //i am the sender
        printf("Sender started (Rank: %d)\n", my_rank);
        for(int q=0; q<comm_sz; q++){
            if(q != p){
                //do not send to myself
                sprintf(greeting, "Sending from sender %d to everyone!", p);
                MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, q, 0, MPI_COMM_WORLD);

            }
        }
    }

    MPI_Finalize();
    return 0;
}