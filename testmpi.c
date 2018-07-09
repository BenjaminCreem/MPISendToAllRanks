#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define arraySize 250

int main(int argc, char **argv)
{
    int rank, numtasks;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *array = (int*)malloc(arraySize*sizeof(int));
   
    if(rank==0)
    {
        printf("Num Tasks: %d\n", numtasks);
    }

    MPI_Status stat;
    int number;
    if(rank==0)
    {
        number=0;
        printf("Rank %d, Number %d\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&number, 1, MPI_INT, numtasks-1, 0, MPI_COMM_WORLD, &stat);
        number++;
        printf("Rank %d, Number %d\n", rank, number);
    }
    if(rank>=1 && rank < numtasks-1)
    {
        MPI_Recv(&number, rank, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &stat);
        number++;
        printf("Rank %d, Number %d\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }
    if(rank==numtasks-1)
    {
        MPI_Recv(&number, rank, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &stat);
        number++;
        printf("Rank %d, Number %d\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }



    //Done with MPI
    MPI_Finalize();
}
