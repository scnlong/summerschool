program hello
  use mpi
  implicit none
  integer :: rank_mpi, size_mpi, ierror
  real(kind=8), dimension(3) :: buffer
  type(mpi_status) :: status_i

  call mpi_init(ierror)
  call mpi_comm_size(mpi_comm_world, size_mpi, ierror)
  call mpi_comm_rank(mpi_comm_world, rank_mpi, ierror)

  ! TODO: say hello! in parallel
  write(*,*) 'Hello!'
  print*,rank_mpi

        
  buffer = (/8.0,8.0,8.0/)
  if (rank_mpi == 0) then
        buffer = (/1.0,2.0,3.0/)
        call mpi_send(buffer, 2, mpi_double_precision, 1, mpi_tag, MPI_COMM_WORLD, ierror)
  elseif (rank_mpi==1) then
        call mpi_recv(buffer, 3, mpi_double_precision, 0, mpi_tag, MPI_COMM_WORLD, status_i, ierror)
  else 
       continue
  endif
  print*,rank_mpi, buffer, " rank_mpi and buffer "

  call mpi_finalize(ierror)

end program hello
