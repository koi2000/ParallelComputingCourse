#include<omp.h>
#include<stdio.h>
#define NUM_THREADS 2
static long num_steps = 100000;
double step;

int main() {
    int nthreads;
    double pi = 0.0;
    step = 1.0/(double)num_steps;
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
            // 将这段代码放在循环内部，会增加索德竞争
            #pragma omp critical
                pi += 4.0/(1.0+x*x);
        }
    }
    pi*=step;
    printf("%lf",pi);
    return 0;
}