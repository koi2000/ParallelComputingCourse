// student name: 宋家庆
// id number: 202000130061

#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;

// add your codes begin
static long MULTIPLIER = 1366;
static long ADDEND = 150889;
static long PMOD = 714025;
long random_last = 0;

long LCG() {
    long random_next;
    random_next = (MULTIPLIER * random_last + ADDEND) % PMOD;
    random_last = random_next;
    return random_next;
}
// add your codes end

int main() {
    double pi;

    double t = omp_get_wtime();
    // add your codes begin
    double x, y;
    double r = 1.0;
    int num_in = 0;
    int tot_num = SIZE;
    for (int i = 0; i < SIZE; i++) {
        x = (double)LCG() / (double)PMOD;
        y = (double)LCG() / (double)PMOD;
        if (x * x + y * y <= r) {
            num_in++;
        }
    }
    pi = 4.0 * (double)(num_in) / (double)(SIZE);
    t = omp_get_wtime() - t;
    // add your codes end
    printf("time %f %d\n", t, SIZE);

    printf("pi %.12f %.12f\n", pi, pi - M_PI);
}
