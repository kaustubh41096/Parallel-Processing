#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "mpi.h"


int main(int argc, char * argv[]){
  int i, n = atoi(argv[1]), *arr = NULL, rank, size;
  clock_t tic = clock();
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  arr = (int *)malloc(n * sizeof(int));
  if(rank == 0){
    for(i = 0; i < n; i++){
      srand(time(0));
      arr[i] = rand();
    }
    for(i = 1; i < size; i++){
      MPI_Send(&arr[0], n, MPI_INT, i, 1, MPI_COMM_WORLD);
    }
    printf("Process : %d\n", rank);
    for(i = 0; i < n; i++){
      printf("arr[%d] : %d ", i, arr[i]);
    }
    printf("\n");
  }
  else{
    MPI_Recv(&arr[0], n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process : %d\n", rank);
    for(i = 0; i < n; i++){
      printf("arr[%d] : %d ", i, arr[i]);
    }
    printf("\n");
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  if(rank == 0){
    clock_t toc = clock();
    printf("Time elapsed : %.16f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC );
  }
  return 0;
}
