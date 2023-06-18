// student name: 宋家庆
// id number: 202000130061

#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;

// add your codes begin
// #define SIZE 10000
static long MULTIPLIER = 1366;
static long ADDEND = 150889;
static long PMOD = 714025;

const int thrd_num = 30;
unsigned long long pseed[10000] = {0};

inline long LCG(long random_last) {
    return (MULTIPLIER * random_last + ADDEND) % PMOD;
}
// add your codes end

int main() {
    double pi;

    double t = omp_get_wtime();
    // add your codes begin
    int nthreads = 0;
    double r = 1.0;
    int num_in = 0;
    long mult_n = MULTIPLIER;
#pragma omp parallel
    {
#pragma omp single
        {
            nthreads = omp_get_num_threads();
            // unsigned long long iseed = PMOD / MULTIPLIER;
            unsigned long long iseed = ADDEND;
            pseed[0] = iseed;
            for (int i = 1; i < nthreads; ++i) {
                iseed =
                    (unsigned long long)((MULTIPLIER * iseed + ADDEND) %
                    PMOD);
                pseed[i] = iseed;
                mult_n = (mult_n * MULTIPLIER) % PMOD;
            }
        }
        int id = omp_get_thread_num();
        int tp_num = 0;
        unsigned long long random_last = (unsigned long long)pseed[id];
        for (int i = 0; i <= SIZE; i += nthreads) {
            random_last =
                (mult_n * random_last + mult_n / MULTIPLIER * ADDEND +
                ADDEND) % PMOD;
            double x = (double)random_last / (double)PMOD;
            random_last = (mult_n * random_last + ADDEND) % PMOD;
            double y = (double)random_last / (double)PMOD;
            if (x * x + y * y <= r * r) {
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
// student name:
// id number:

#include <math.h>
#include <omp.h>
#include <stdio.h>

#include <vector>
using namespace std;

// add your codes begin
#define MULTIPLIER 1366
#define ADDEND 150889
#define PMOD 714025
#define NUM_THREADS 50
long random_last = 0;
long random_last_1 = 95;
long random_last_2 = 36;

double random_omp(long &random_last) {
    long random_next = (MULTIPLIER * random_last + ADDEND) % PMOD;
    random_last = random_next;
    return ((double)random_next / (double)PMOD);
}

// add your codes end

int main() {
    double pi;

    double t = omp_get_wtime();
    // add your codes begin
    // long seed_x[20]={1,2,3,4,5,6,7,8,9,10};
    // long seed_y[20]={1,2,3,4,5,6,7,8,9,10};
    long result[NUM_THREADS] = {0};

    long Ncirc = 0;
    double x, y;
    long pseed[NUM_THREADS];

    int r = 1;
    int iseed = PMOD / MULTIPLIER;  // just pick a seed
    pseed[0] = iseed;
    int mult_n = MULTIPLIER;
    for (long i = 0; i < NUM_THREADS; ++i) {
        iseed = (unsigned long long)((MULTIPLIER * iseed) % PMOD);
        pseed[i] = iseed;
    }

    // long random_last;
    long random_last = 0;
// long random_last,random_last_1,random_last_2;
#pragma omp parallel num_threads(NUM_THREADS) private(x, y,random_last) reduction(+ : Ncirc) //private的话每次执行如下代码变量都会是相同的初值不会改变
    {
        int id = omp_get_thread_num();

        random_last = (unsigned long long)pseed[id];
        for (long i = 0; i < SIZE / NUM_THREADS; i++)  // 问题是一
        {
            x = random_omp(random_last);  // pseed y
            y = random_omp(random_last);  // pseed x
            if ((x * x + y * y) <= r * r) {
                Ncirc++;
            }
        }
    }

    pi = 4.0 * ((double)Ncirc / ((double)SIZE));
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    printf("pi %.12f %.12f\n", pi, pi - M_PI);
}