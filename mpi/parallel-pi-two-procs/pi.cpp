#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 840;

int main(int argc, char** argv)
{

  int rank;
  int num_procs;  

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&num_procs);

  printf("Computing approximation to pi with N=%d\n", n);

  int istart = 1;
  int istop = n;

  double pi = 0.0;
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    pi += 1.0 / (1.0 + x*x);
  }

  pi *= 4.0 / n;

  double pi_p2 = 0.0;

  if (rank==1){
  double pi_tmp = 0.0;
  for (int i=istart; i <= istop/2; i++) {
    double x = (i - 0.5) / n;
    pi_tmp += 1.0 / (1.0 + x*x);
  }
  MPI_Send(&pi_tmp,1,MPI_INT,0,0,MPI_COMM_WORLD) ;
  } else if (rank==0) {
  double pi_tmp;
  for (int i=(istop/2+1); i <= istop; i++) {
    double x = (i - 0.5) / n;
    pi_p2 += 1.0 / (1.0 + x*x);
  }
  MPI_Recv(&pi_tmp,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
  pi_p2 += pi_tmp;
  pi_p2 *= 4.0/n;
  }

  if (rank==0) {
  printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);
  printf("Approximate 2 procs pi=%18.16f (exact pi=%10.8f)\n", pi_p2, M_PI);
  }

  MPI_Finalize();

}
