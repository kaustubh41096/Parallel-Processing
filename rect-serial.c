#include<stdio.h>
#include<math.h>
#include<time.h>

double func(double x, int n){
  double ans;
  ans = 4.0 / (1.0 + x*x);
  return ans;
}

double comp(double end, int n){
  double height, width, area;
  height = func(end, n);
  width = 1.0 / (double)n;
  area = height * width;
  return area;
}

int main(int argc, char * argv[]){
  clock_t tic = clock();
  int n = 200000;
  double pi = 0.0, pi16 = 3.141592653589793238462643, i;
  for(i = 0.0; i <= 1.0; i += 1.0 / (double)n){
    pi = pi + comp(i + 1 / (double)n, n);
  }
  clock_t toc = clock();
  printf("Execution Time = %.16f\n", (double)(toc - tic) / CLOCKS_PER_SEC);
  printf("The value of pi is %.16f and error is %.16f\n", pi, fabs(pi - pi16));
  return 0;
}
