// Main solver routines for heat equation solver

#include <mpi.h>

#include "heat.hpp"

// Exchange the boundary values
void exchange(Field& field, const ParallelData parallel)
{
    double *data;  
    double *sbuf_up, *sbuf_down, *rbuf_up, *rbuf_down;

    data = field.temperature.data();
#ifdef GPU_MPI
#pragma omp target data use_device_ptr(data)
#endif
    {

    // Send to the up, receive from down
    sbuf_up = data + field.ny + 2; // upper data
    rbuf_down = data + (field.nx + 1) * (field.ny + 2); // lower halo

    MPI_Sendrecv(sbuf_up, field.ny + 2, MPI_DOUBLE,
                 parallel.nup, 11,
                 rbuf_down, field.ny + 2, MPI_DOUBLE, 
                 parallel.ndown, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Send to the down, receive from up
    sbuf_down = data + field.nx * (field.ny + 2); // lower data
    rbuf_up = data; // upper halo

    MPI_Sendrecv(sbuf_down, field.ny + 2, MPI_DOUBLE, 
                 parallel.ndown, 12,
                 rbuf_up, field.ny + 2, MPI_DOUBLE,
                 parallel.nup, 12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } // end target data
}

// Update the temperature values using five-point stencil */
void evolve(Field& curr, Field& prev, const double a, const double dt)
{

  // Compilers do not necessarily optimize division to multiplication, so make it explicit
  auto inv_dx2 = 1.0 / (prev.dx * prev.dx);
  auto inv_dy2 = 1.0 / (prev.dy * prev.dy);

  // Help the compiler avoid being confused by the structs
  double *currdata = curr.temperature.data();
  double *prevdata = prev.temperature.data();

  int nx = curr.nx;
  int ny = curr.ny;

  // Determine the temperature field at next time step
  // As we have fixed boundary conditions, the outermost gridpoints
  // are not updated.
  #pragma omp target teams distribute parallel for collapse(2)
  for (int i = 1; i < nx + 1; i++) {
    for (int j = 1; j < ny + 1; j++) {
      int ind = i * (ny + 2) + j;
      int ip = (i + 1) * (ny + 2) + j;
      int im = (i - 1) * (ny + 2) + j;
      int jp = i * (ny + 2) + j + 1;
      int jm = i * (ny + 2) + j - 1;
      currdata[ind] = prevdata[ind] + a*dt*
	    ((prevdata[ip] - 2.0*prevdata[ind] + prevdata[im]) * inv_dx2 +
	     (prevdata[jp] - 2.0*prevdata[ind] + prevdata[jm]) * inv_dy2);
    }
  }

}

/* Start a data region and copy temperature fields to the device */
void enter_data(Field& curr, Field& prev)
{
    int nx, ny;
    double *currdata, *prevdata;

    currdata = curr.temperature.data();
    prevdata = prev.temperature.data();
    nx = curr.nx;
    ny = curr.ny;

#pragma omp target enter data \
    map(to: currdata[0:(nx+2)*(ny+2)], prevdata[0:(nx+2)*(ny+2)])
}
  
/* End a data region and copy temperature fields back to the host */
void exit_data(Field& curr, Field& prev)
{
    int nx, ny;
    double *currdata, *prevdata;
  
    currdata = curr.temperature.data();
    prevdata = prev.temperature.data();
    nx = curr.nx;
    ny = curr.ny;

#pragma omp target exit data \
    map(from: currdata[0:(nx+2)*(ny+2)], prevdata[0:(nx+2)*(ny+2)])
}

/* Copy a temperature field from the device to the host */
void update_host(Field& temperature) 
{   
    int nx, ny;
    double *data;

    data = temperature.temperature.data();
    nx = temperature.nx;
    ny = temperature.ny;

#pragma omp target update from(data[0:(nx+2)*(ny+2)])
}   

void update_device(Field& temperature) 
{   
    int nx, ny;
    double *data;

    data = temperature.temperature.data();
    nx = temperature.nx;
    ny = temperature.ny;

#pragma omp target update to(data[0:(nx+2)*(ny+2)])
}   

