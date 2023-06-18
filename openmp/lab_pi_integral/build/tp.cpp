// student name: Junhao Xu
// id number: 201900122025

/*#include <omp.h>
#include <math.h>
#include <stdio.h>
using namespace std;

// add your codes begin
#define SIZE 10000000
static long num_steps = SIZE;
double step;
// add your codes end

int main()
{
  double pi=0.0;

  double t = omp_get_wtime();
  // add your codes begin
  step = 1.0 / (double)num_steps;
  omp_set_num_threads(100);


  #pragma omp parallel
  {
    int i;
    double x, sum;
    int id = omp_get_thread_num();
    int nthrds = omp_get_num_threads();
    // double temp1 = 0.5*step;
    // double temp2 = nthrds*step;
    // double end = num_steps*step;
    x = (id) * step;
    double margin = nthrds*step;
    for (i = id + nthrds,sum= 0.0; i < num_steps; i+=nthrds)
    {
      x += margin;
      // x = (i + 0.5) * step;
      sum += 4.0 / (1.0 + x * x);
    }
    // sum = sum*step;
    #pragma omp critical
      pi+=sum*step;

    // #pragma atomic
    //   pi+=sum;
  }
  // pi+=0.000100000001;
  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, SIZE);

  printf("pi %.12f %.12f\n", pi, pi - M_PI);
}*/

#include <omp.h>
static long num_steps = 100000;
double step;
#define NUM_THREADS 2
void main() {
  double pi;
  step = 1.0 / (double)num_steps;
  omp_set_num_threads(NUM_THREADS);
  int nthreads = 0;
#pragma omp parallel
  {
    int i, id, nthrds;
    double x, sum;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    if (id == 0)
      nthreads = nthrds;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    for (i = id, sum = 0.0; i < num_steps; i = i + nthreads) {
      x = (i + 0.5) * step;
      sum += 4.0 / (1.0 + x * x);
    }
    sum = sum * step;
#pragma atomic
