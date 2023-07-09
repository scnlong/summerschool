program parallel_two_steps_pi
  use iso_fortran_env, only : REAL64
  use mpi

  implicit none

  integer, parameter :: dp = REAL64

  integer, parameter :: n = 10000

  integer :: i, istart, istop, ierror, myid

  type(mpi_status) :: status

  real(dp) :: pi, pi2, x

  call mpi_init(ierror)
  call mpi_comm_rank(MPI_COMM_WORLD, myid, ierror)

  if (myid == 0) then
  write(*,*) "Computing approximation to pi in serial with n=", n

  istart = 1
  istop = n

  pi = 0.0
  do i = istart, istop
    x = (i - 0.5) / n
    pi = pi + 1.0 / (1.0 + x**2)
  end do

  pi = pi * 4.0 / n
  write(*,'(A,F18.16,A,F10.8,A)') 'Approximate pi=', pi, ' (exact pi=', 4.0*atan(1.0_dp), ')'
  endif
  call mpi_barrier(MPI_COMM_WORLD,ierror)

  if (myid == 0) then
     istart = 1
     istop = n/2

     pi = 0.0
     do i = istart, istop
       x = (i - 0.5) / n
       pi = pi + 1.0 / (1.0 + x**2)
     end do
     call mpi_send(pi,1,MPI_double_precision, 1, 111, MPI_COMM_WORLD, ierror)
  elseif (myid == 1) then
     istart = n/2+1
     istop = n

     pi2 = 0.0
     do i = istart, istop
       x = (i - 0.5) / n
       pi2 = pi2 + 1.0 / (1.0 + x**2)
     end do
     
     call mpi_recv(pi,1,MPI_double_precision,0, 111, MPI_COMM_WORLD, status, ierror)
     pi = (pi + pi2) * 4.0 / n
  
     write(*,'(A,F18.16,A,F10.8,A)') 'Approximate pi in 2 processors =', pi, ' (exact pi=', 4.0*atan(1.0_dp), ')'

  else
     continue
  endif

  call mpi_finalize(ierror)
  


end program

