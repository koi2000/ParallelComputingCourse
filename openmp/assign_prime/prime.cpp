// student name: 宋家庆
// id number: 202000130061

#include <math.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// add your codes begin

// #define SIZE 10000000

int cnt;
bool st[SIZE];
bool is_prime[SIZE];

// add your codes end

int main() {
    vector<long> prime;

    double t = omp_get_wtime();
    omp_set_num_threads(30);
    // 根据N的不同大小需要调整
    int sz = SIZE;
    if (SIZE >= 100000000) {
        sz /= 15;
    }
    prime.resize(sz);
    // 埃式筛法+数理推导
    for (int i = 2; i <= (int)sqrt(SIZE); i++) {
        if (!st[i]) {
            // prime.push_back(i);
#pragma omp parallel for
            for (int j = i + i; j <= SIZE; j += i) {
                if (!st[j]) st[j] = true;
            }
        }
    }
    st[0] = st[1] = 1;
    int cnt = 0;
#pragma omp parallel
    {
        int id, i, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        vector<int> res;
        int num = SIZE;
        if (id != 2 && id % 2 == 0 && nthrds % 2 == 0) {
        } else {
            for (i = id; i <= SIZE; i += nthrds) {
                if (st[i] == 0) {
                    res.push_back(i);
                }
            }
        }

#pragma omp critical
        for (int j = 0; j < res.size(); j++) {
            prime[cnt++] = res[j];
        }
    }
    prime.resize(cnt);

    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %ld\n", t, long(SIZE));

    printf("prime");
    sort(prime.begin(), prime.end());
    for (long i = 0; i < prime.size(); i++) printf(" %ld", prime[i]);
    printf("\nsize %ld\n", prime.size());
}
