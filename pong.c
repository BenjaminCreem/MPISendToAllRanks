#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define SIZE 10

void printArray(int *array, int n);
void addToArray(int *array, int n);

int main(int argc, char **argv)
{
    int rank, numtasks;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *array = (int*)malloc(SIZE*sizeof(int));
   
    if(rank==0)
    {
        printf("Num Tasks: %d\nSize: %d\n", numtasks, SIZE);
    }

    MPI_Status stat;

    if(rank==0)
    {
        for(int i = 0; i < SIZE; i++)
        {
            array[i] = i;
        }
        printf("Rank %d\n", rank);
        printArray(array, SIZE);

        for(int i = 0; i < numtasks-1; i++)
        {   
            MPI_Send(array, SIZE, MPI_INT, i+1, 0, MPI_COMM_WORLD);
            MPI_Recv(array, SIZE, MPI_INT, i+1, 0, MPI_COMM_WORLD, &stat);
            printf("Rank %d\n", rank);
            addToArray(array, SIZE);
            printArray(array, SIZE);
        }
    }
    if(rank>=1 && rank <= numtasks)
    {
        MPI_Recv(array, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
        printf("Rank %d\n" ,rank);
        addToArray(array, SIZE);
        printArray(array, SIZE);
        MPI_Send(array, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    

    //Done with MPI
    MPI_Finalize();
}

void printArray(int *array, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void addToArray(int *array, int n)
{
    for(int i = 0; i < n; i++)
    {
        array[i] = array[i]+1;
    }
}
