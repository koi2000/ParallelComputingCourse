// student 宋家庆:
// id 202000130061:

#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;

// add your codes begin
//#define SIZE 10000000
static long num_step = SIZE;
// add your codes end

int main() {
  double pi;

  double t = omp_get_wtime();
  // add your codes begin
  int i;
  double sum = 0.0;
  double step = 1.0 / (double)num_step;
  omp_set_num_threads(10);
#pragma omp parallel
  {
    double x;
#pragma omp for reduction(+ : sum)
    for (i = 0; i < num_step; i++) {
      x = (i + 0.5) * step;
      sum = sum + 4.0 / (1.0 + x * x);
    }
  }
  pi = step * sum;
  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, SIZE);

  printf("pi %.12f %.12f\n", pi, pi - M_PI);
}
