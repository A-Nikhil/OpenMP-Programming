#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"
#include <omp.h>

int main(int argc, char* argv[])
{
	int niter = 100000;					
	int myid;						
	double x,y;						
	int i;							
    int count=0;						
	double z;						
	double pi;						
	int reducedcount;					
	int reducedniter;					
	int ranknum = 0;					
	int numthreads = 4;					
	MPI_Init(&argc, &argv);					
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);			
	MPI_Comm_size(MPI_COMM_WORLD, &ranknum);		

	if(myid != 0)						
	{
		
		#pragma omp parallel firstprivate(x, y, z, i) reduction(+:count) num_threads(numthreads)
		{
			srand48((int)time(NULL) ^ omp_get_thread_num());	
			for (i=0; i<niter; ++i)					
			{
				x = (double)drand48();				
				y = (double)drand48();				
				z = ((x*x)+(y*y));				
				if (z<=1)
				{
					++count;					
				}	
			}
		} 
	}
	MPI_Barrier(MPI_COMM_WORLD);
	
	MPI_Reduce(&count, &reducedcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	

	reducedniter = numthreads*niter*(ranknum-1);					
	MPI_Barrier(MPI_COMM_WORLD);
	if (myid == 0)
	{
		pi = ((double)reducedcount/(double)reducedniter)*4.0;
		// pi = 3.14;
		printf("Pi: %f\n", pi);			
	}
	MPI_Finalize();
	return 0;
}