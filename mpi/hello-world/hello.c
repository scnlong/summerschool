#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{ 
    int ntasks; int my_rank; int ierror;
    ierror = MPI_Init(&argc, &argv);
    ierror = MPI_Comm_size(MPI_COMM_WORLD,&ntasks);
    ierror = MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    // TODO: say hello! in parallel
    printf("Hello!\n");
    printf("This is rank %d in all %d ranks. \n", my_rank, ntasks);
}
