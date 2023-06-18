// student 宋家庆:
// id 202000130061:

#include <math.h>
#include <omp.h>
#include <stdio.h>
using namespace std;

// add your codes begin
#define SIZE 25
#define N 100000000
// add your codes end
bool check(int x) {
    if (x < 2) return false;
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    double pi;

    double t = omp_get_wtime();
    // add your codes begin

    omp_set_num_threads(SIZE);
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (check(i)) count++;
    }
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    printf("%d\n", count);
}
