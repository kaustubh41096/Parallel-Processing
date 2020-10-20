#include<stdio.h>
#include<math.h>
#include "mpi.h"

double func(double x, int n){
    double ans;
    ans = 4.0/(1.0 + (x/(double)n)*(x/(double)n));
    return ans;
}

double compute(int start, int end, int ivs, int size){
  double ans;
  int i;
  for(i = start; i<end; i = i + 2){
      ans = ans + 4.0*func((double)i, ivs) + 2.0*func(((double)i + 1), ivs);
  }
  return ans;
}

int main(int argc, char * argv[]){
  int i, j, n = 10000, size, rank;
  double res = 0.0, pi = 0.0, res2, pi16 = 3.141592653589793238462643, buf = 0.0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
  double buffer[size];
  if(rank == 0){
    for(i = 1; i<size; i++){
      MPI_Send(&n, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
    }
    res2 = func(0.0, n) - func((double)n, n);
    res = res2 + compute((floor(n/size)*rank + 1), ((floor(n/size)*rank + 1) + floor(n/size)), n, size);
    buffer[0] = res;
    for(j=1; j<size; j++){
			MPI_Recv(&buffer[j], 1, MPI_DOUBLE, j, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
    for(j=0; j<size; j++){
      buf = buf + buffer[j];
    }
    pi = (buf)/(3.0 * (double)n);
    printf("The value of pi is %.16f with error %.16f\n",pi, fabs(pi-pi16));
  }
  else{
    MPI_Recv(&n, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if(rank == size - 1){
      res = compute((floor(n/size)*rank + 1), n+1, n, size);
      MPI_Send(&res, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
    else{
      res = compute((floor(n/size)*rank + 1), ((floor(n/size)*rank + 1) + floor(n/size)), n, size);
      MPI_Send(&res, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
  return 0;
}
