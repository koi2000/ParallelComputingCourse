// student 宋家庆:
// id 202000130061:

/*#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;

// add your codes begin
//#define SIZE 25

static long num_step = 10000000;
// add your codes end

int main() {
  double pi;

  double t = omp_get_wtime();
  // add your codes begin
  double step = 1 / (double)num_step;

  omp_set_num_threads(25);
  int real_num = 0;
  int nthreads;

#pragma omp parallel
  {
    int id,i,nthrds;
    id = omp_get_thread_num();
    // i为每个线程私有，每个线程只需执行自己需要执行的次数即可
    // 这里的x和sum也不再共享，而是每个线程私有一份
    double x, sum = 0.0;
    nthrds = omp_get_num_threads();
    if (id == 0) {
        nthreads = omp_get_num_threads();
        //printf("-----%d",real_num);
    }
    //id = omp_get_thread_num();
    //nthrds = omp_get_num_threads();
    //printf("%d ",id);
    x = (id)*step;
    double margin = nthrds*step;
    // 每个线程只执行循环中自己需要执行的部分
    for (i = id; i < num_step; i += nthreads) {
      //x = (i + 0.5) * step;
      x = x + margin;
      sum += 4.0 / (1.0 + x * x);
    }
    #pragma atomic
        pi += sum* step; 
    //#pragma critical (critical1) 
    //    pi += sum; 
  }
  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, SIZE);

  printf("pi %.12f %.12f\n", pi, pi - M_PI);
}
*/

// student name: Junhao Xu
// id number: 201900122025

#include <omp.h>
#include <math.h>
#include <stdio.h>
using namespace std;

// add your codes begin

static long num_steps = 100;
double step;
// add your codes end

int main()
{
  double pi=0.0;

  double t = omp_get_wtime();
  // add your codes begin
  step = 1.0 / (double)num_steps;
  omp_set_num_threads(100);
  
    int i = 0;
  #pragma omp parallel
  {
    i++;
    int id = omp_get_thread_num();
    printf("%d\n",i);
  }
  // pi+=0.000100000001;
  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, 25);

  printf("pi %.12f %.12f\n", pi, pi - M_PI);
}
