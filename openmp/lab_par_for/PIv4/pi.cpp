#include<omp.h>
#include<stdio.h>
#include<math.h>
#define NUM_THREADS 4
static long num_steps = 10000000;
double step;

int main() {
    int nthreads;
    double pi = 0.0;
    step = 1.0/(double)num_steps;

    double t = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i,id,nthrds;
        double x,sum;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id==0) nthreads = nthrds;
        for (i = id,sum = 0.0; i < num_steps; i+=nthreads) {
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
        sum *= step;
        // 这里使用了一个critical，确保每次都只会有一个线程访问该段代码
        // 与上一个版本相比，好处在于不需要开辟空间存储了
        // 但缺点是引入了锁，会导致性能的下降
        #pragma atomic 
        {
            pi += sum;
        }
    }
    //printf("%lf",pi);

    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, NUM_THREADS);

    printf("pi %.12f %.12f\n", pi, pi - M_PI);
    return 0;
}