#include<stdio.h>
#include<math.h>
#include<time.h>

double func(double x, int n){
  double ans;
  ans = 4.0 / (1.0 + x / (double)n*x / (double)n);
  return ans;
}

int main(){
  clock_t tic = clock();
  int n = 200000, i;
  double pi, res = 0.0, res2 = 0.0, pi16 = 3.141592653589793238462643;
  res = func(0.0, n) - func((double)n, n);
  for(i = 1; i < n; i += 2){
    res = res + (4.0*func((double)i, n) + 2.0*func((double)i + 1, n));
  }
  pi = (res) / (3.0 * (double)n);
  clock_t toc = clock();
  printf("Execution Time = %.16f\n", (double)(toc - tic) / CLOCKS_PER_SEC);
  printf("The value of pi is %.16f and error is %.16f\n", pi, fabs(pi - pi16));
  return 0;
}
