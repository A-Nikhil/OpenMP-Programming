/*
* Running the code
mpicc sendRecv.c
mpiexec -n 2 ./a.out
*/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
 

int main(int argc,char **argv) {
  int myid, numprocs;
  int tag,source,destination,count;
  int buffer;

  MPI_Status status;
 
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
  tag = 1234;
  source = 0;
  destination = 1;
  count = 1;
    
  if(myid == source){
    buffer = 5678;
    MPI_Send(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD);
    printf("processor %d  sent %d\n",myid,buffer);
  }

  if(myid == destination){
    MPI_Recv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    printf("processor %d  got %d\n",myid,buffer);
  }

  MPI_Finalize();
}
