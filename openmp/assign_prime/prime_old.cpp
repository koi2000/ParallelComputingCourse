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

#define SIZE 100
int cnt;
bool st[SIZE];
bool is_prime[SIZE];

// add your codes end

int main() {
    vector<long> prime;

    double t = omp_get_wtime();
    omp_set_num_threads(30);
    //  add your codes begin
    //  普通筛法
    //  for (int i = 2; i < SIZE; i++) {
    //      if (!st[i]) prime.push_back(i);

    //     for (int j = i; j < SIZE; j += i) {
    //         if (!st[j]) st[j] = true;
    //     }
    // }

    // 数理推导
    //     for (int i = 2; i * i <= SIZE; i++) {
    // // if (!st[i]) prime.push_back(i);
    // #pragma omp paraller for
    //         for (int j = i; j <= SIZE; j += i) {
    //             if (!st[j]) st[j] = true;
    //         }
    //     }

    //     for (long i = 2; i * i <= SIZE; i++) {
    //         if (i % 2 != 0 && st[i] == 0) {
    //             prime.push_back(i);
    //         }
    //         if (i % 2 == 0) continue;
    // #pragma omp parallel for
    //         for (int j = i * i; j <= SIZE; j = j + i) {
    //             if (st[j] == 0) st[j] = 1;
    //         }
    //     }
    //     for (int i = sqrt(SIZE); i <= SIZE; i++) {
    //         if (i % 2 != 0 && st[i] == 0) {
    //             prime.push_back(i);
    //         }
    //     }

    // #pragma omp parallel for num_threads(10)
    //  for (int i = 2; i <= (int)sqrt(SIZE); i++) {
    //      if (st[i]) {
    //          #pragma omp parallel for num_threads(10)
    //          for (int j = i; i * j <= SIZE; j++) {
    //              if (st[i * j] == 0) st[i * j] = true;
    //          }
    //      }
    //  }
    //  for (int i = 2; i <= SIZE; i++) {
    //      if (st[i] == 0) {
    //          prime.push_back(i);
    //      }
    //  }

    prime.resize(SIZE/10);
    // 埃式筛法+数理推导
    // #pragma omp parallel for num_threads(10)
    for (int i = 2; i <= (int)sqrt(SIZE); i++) {
        if (!st[i]) {
            // prime.push_back(i);
#pragma omp parallel for
            for (int j = i + i; j <= SIZE; j += i) {
                if (!st[j]) st[j] = true;
            }
        }
    }
    // #pragma omp parallel for shared(prime)
    // for (int i = (int)sqrt(SIZE); i <= SIZE; i++) {
    //     if (st[i] == 0) {
    //         prime.push_back(i);
    //     }
    // }
    st[0] = st[1] = 1;
    int cnt = 0;
#pragma omp parallel
    {
        int id, i, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        vector<int> res;
        int num = SIZE;
        //int res[100000];
        if (id != 2 && id % 2 == 0 && nthrds % 2 == 0) {
        } else {
            for (i = id; i <= SIZE; i += nthrds) {
                if (st[i] == 0) {
                    res.push_back(i);
                    //res[cnt++] = i;
                }
            }
        }

#pragma omp critical
        // prime.insert(prime.end(),res.begin(),res.end());
        for (int j = 0; j < res.size(); j++) {
            //prime.push_back(res[j]);
            prime[cnt++] = res[j];
        }
        // for (int j = 0; j < cnt; j++) {
        //     prime.push_back(res[j]);
        // }
    }
    prime.resize(cnt);

    // 线性筛法
    //     for (int i = 2; i < SIZE; i++) {
    //         if (!st[i]) {
    //             prime.push_back(i);
    //         }
    //         int n = prime.size();
    //         volatile bool flag = false;
    // #pragma omp parallel for shared(flag)
    //         for (int j = 0; j < n; j++) {
    //             if (flag) continue;
    //             //if (prime[j] * i >= SIZE) flag = true;
    //             //if (st[prime[j] * i] == 0) st[prime[j] * i] = true;
    //             //if (i % prime[j] == 0) flag = true;
    //         }
    //     }
    // for (int i = 2; i < SIZE; i++) {
    //     if (!st[i]) {
    //         prime.push_back(i);
    //     }
    //     for (int j = 0; prime[j] * i < SIZE && j < prime.size(); j++) {
    //         st[prime[j] * i] = true;
    //         if (i % prime[j] == 0) break;
    //     }
    // }

    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %ld\n", t, long(SIZE));

    printf("prime");
    sort(prime.begin(), prime.end());
    // for (long i = 0; i < prime.size(); i++) printf(" %ld", prime[i]);
    printf("\nsize %ld\n", prime.size());
}
