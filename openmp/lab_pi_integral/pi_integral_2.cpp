// student 宋家庆:
// id 202000130061:

#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;

// add your codes begin
//#define SIZE 25

static long num_step = SIZE;
// add your codes end

int main() {
  double pi;

  double t = omp_get_wtime();
  // add your codes begin
  double step = 1 / (double)num_step;

  omp_set_num_threads(10);
  int real_num = 0;
  int nthreads;

#pragma omp parallel
  {
    int id,i,nthrds;
    id = omp_get_thread_num();
    // i为每个线程私有，每个线程只需执行自己需要执行的次数即可
    // 这里的x和sum也不再共享，而是每个线程私有一份
    double x = 0.0, sum = 0.0;
    nthrds = omp_get_num_threads();
    //x = (id)*step;
    //double real_step = nthrds*step;
    // 每个线程只执行循环中自己需要执行的部分
    for (i = id; i < num_step; i += nthrds) {
      x = (i + 0.5) * step;
      //x = x + real_step;
      sum += 4.0 / (1.0 + x * x);
    }
    // #pragma atomic
    //     pi += sum* step; 
    //printf("%.12f ",sum);
    // 如果使用atomic要注意，atomic中只支持简单的操作
    // 使用atomic需要将乘法在外面做，然后内部只有加法
    #pragma critical (critical1) 
        pi += sum * step; 
  }
  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, SIZE);

  printf("pi %.12f %.12f\n", pi, pi - M_PI);
}
