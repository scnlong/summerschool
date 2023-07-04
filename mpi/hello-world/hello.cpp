#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int ierror, ntasks, my_rank;
    ierror = MPI_Init(&argc, &argv);
    ierror = MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    ierror = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    ierror = MPI_Finalize(); 
    // TODO: say hello! in parallel
    std::cout << "Hello from rank "<< my_rank << " in all " <<  ntasks << " ranks."  << std::endl;
}
