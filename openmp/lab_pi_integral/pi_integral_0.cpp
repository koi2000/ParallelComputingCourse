// student 宋家庆:
// id 202000130061:

#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;


// add your codes begin
// #define SIZE 10000000
static long num_steps = SIZE;
double step;
// add your codes end

int main() {
  double t = omp_get_wtime();
  // add your codes begin
  int i;
  double x, pi, sum = 0.0;
  //omp_set_num_threads(SIZE);
  step = 1.0 / (double)num_steps;
  for (int i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
  }
  pi = step * sum;

  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, SIZE);

  printf("pi %.12f %.12f\n", pi, pi - M_PI);
}
