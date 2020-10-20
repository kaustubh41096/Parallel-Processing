#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<time.h>
#include "mpi.h"


double function(double x){
		double ans;
		ans = 4.0/ (1.0 + x*x);
		return ans;
}


double compute(double end, int pid, int ivs){
		double height, width, area;
		height = function(end);
		width = 1/ (double)ivs;
		area = height * width;
		return area;
}


int main(int argc,char *argv[])
{
	clock_t tic = clock();
	int i, j, n, flag;
	double res, pi = 0.00, lsum = 0.0, end;
	double pi16 = 3.141592653589793238462643;
	int rank, size;
  MPI_Status status;
  MPI_Request req1, req2;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	double buffer[size];
	if(rank==0){
		n = 100000;
		for(i=1;i<size;i++){
			MPI_Isend(&n, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &req1);
		}
		for(i = 0; i < n; i += size){
			res = res + compute(((double)i + 1.0)/ (double)n, 0, n);
		}
		buffer[0] = res;
		for(i=1;i<size;i++){
			MPI_Irecv(&buffer[i], 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &req2);
      MPI_Wait(&req2, &status);
		}
		for(i = 0; i < size; i++){
			pi = pi + buffer[i];
		}
		clock_t toc = clock();
		printf("Time elapsed : %.16f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC );
		printf("The value of pi is %.16f with an error of %.16f\n", pi, fabs(pi - pi16));
	}
	else{
			MPI_Irecv(&n, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &req1);
      MPI_Wait(&req1, &status);
			for(i = rank; i < n; i += size){
				lsum = lsum + compute(((double)i + 1.0)/ (double)n, rank, n);
			}
			MPI_Isend(&lsum, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, &req2);
  }
  MPI_Finalize();
	return 0;
}
