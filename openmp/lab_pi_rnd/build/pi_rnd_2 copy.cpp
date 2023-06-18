// student name: 宋家庆
// id number: 202000130061

#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;

// add your codes begin
// #define SIZE 10000
static long MULTIPLIER1 = 1366;
static long ADDEND1 = 150889;
static long PMOD1 = 714025;

static long MULTIPLIER2 = 1277;
static long ADDEND2 = 524849;
static long PMOD2 = 981293;

const int thrd_num = 30;
unsigned long long pseed[10000];

inline long LCG(long random_last) {
    return (MULTIPLIER2 * random_last + ADDEND2) % PMOD2;
}
// add your codes end

int main() {
    double pi;

    double t = omp_get_wtime();
    // add your codes begin
    int nthreads = 0;
    double r = 1.0;
    int num_in = 0;
#pragma omp parallel
    {
#pragma omp single
        {
            nthreads = omp_get_num_threads();
            unsigned long long iseed = PMOD1 / MULTIPLIER1;  // just pick a seed
            pseed[0] = iseed;
            for (int i = 1; i < nthreads; ++i) {
                iseed = (unsigned long long)((MULTIPLIER1 * iseed) % PMOD1);
                pseed[i] = iseed;
            }
        }
        int id = omp_get_thread_num();
        int tp_num = 0;
        long long random_last = (unsigned long long)pseed[id];
        for (int i = 0; i < SIZE; i += nthreads) {
            random_last = LCG(random_last);
            double x = (double)random_last / (double)PMOD2;
            random_last = LCG(random_last);
            double y = (double)random_last / (double)PMOD2;
            if (x * x + y * y <= r) {
                tp_num++;
            }
        }
#pragma omp critical
        num_in += tp_num;
    }

    pi = 4.0 * (double)(num_in) / (double)(SIZE);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    printf("pi %.12f %.12f\n", pi, pi - M_PI);
}
