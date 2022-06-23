#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <math.h>
int semiprime(int n);
int main(int argc, char **argv)
{
 int ntasks, rank;
 double starttime, endtime; 
 if (argc != 2)
	exit(1);
 int limit = 0;
 limit = atoi(argv[1]);

 MPI_Init(&argc, &argv);
 starttime = MPI_Wtime();
 MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 int min, max;
 double del = (double) limit/ntasks;
 min = (rank == 0)? 2 : (int)(rank*del) + 1;
 max = (rank == ntasks-1)? limit : (int)((rank+1)*del);

 int send = 0;
 int count = 0;
 int j = min;
 while (j <= max)
 {
	if (semiprime(j))
		send++;
	j++;
 }
 MPI_Allreduce(&send, &count, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
 endtime = MPI_Wtime();
 if (rank == 0)
 {
 	printf ("Deadly number of %d is %d", limit, count);
        printf("(Elapsed time %.2lf sec)\n",endtime-starttime);
 }
 MPI_Finalize();
}

int semiprime(int n)
{
	int p = 2, f = 0;
	while(f < 2 && p*p)
	{
		while(0 == n % p)
		{
			n/=p;
			 f++;
		}
		p++;
	}
	return f + (n > 1) == 2;
}














