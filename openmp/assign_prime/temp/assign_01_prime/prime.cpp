// student 宋家庆:
// id 202000130061:

#include <math.h>
#include <omp.h>
#include <stdio.h>

#include <vector>
using namespace std;

// add your codes begin
#define SIZE 10
#define N 100000000

int primes[N], cnt;
bool st[N];

bool is_prime[N];

// add your codes end
bool check1(int x) {
    if (x < 2) return false;
    if (x > 10 && x % 10 == 5) return false;
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

bool check2(int x) {
    if (x < 2) return false;
    int nthread = SIZE;
    int flag = 0;
    omp_set_num_threads(SIZE);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        if (id == 0) nthread = omp_get_num_threads();
        int fg = 0;
        for (int i = 2; i <= x / i; i += nthread) {
            if (x % i == 0) {
                fg++;
                break;
            }
        }
#pragma omp atomic
        flag += fg;
    }
    if (flag) {
        return false;
    }

    return true;
}

bool check3(int x) {
    if (x < 2) return false;
    if (x > 10 && x % 10 == 5) return false;
    for (size_t i = 0; i < x; i++) {
        /* code */
    }
    return false;
}

int main() {
    double pi;

    double t = omp_get_wtime();
    // add your codes begin

    omp_set_num_threads(SIZE);

    int count = 0;
    int nthread = SIZE;
    // 普通筛法
    //     for (int i = 2; i <= N; i++) {
    //         if (!st[i]) primes[cnt++] = i;  // 把素数存起来
    // #pragma omp for
    //         for (int j = i; j <= N;
    //              j += i) {  // 不管是合数还是质数，都用来筛掉后面它的倍数
    //             if (!st[j]) st[j] = true;
    //         }
    //     }
    
    for (long i = 2; i * i <= N; i++) {
#pragma omp parallel for
        for (int j = i * i; j <= N; j = j + i) {
            if (st[j] == 0) st[j] = 1;
        }
    }

    // 埃式筛法
    //     for (int i = 2; i <= N; i++) {
    //         if (!st[i]) {
    //             primes[cnt++] = i;
    // #pragma omp for
    //             for (int j = i; j <= N; j += i)
    //                 if (!st[j]) st[j] = true;  //
    //                 可以用质数就把所有的合数都筛掉；
    //         }
    //     }
    // 线性筛法
    // for (int i = 2; i <= N; i++) {
    //     if (!st[i]) primes[cnt++] = i;
    //     for (int j = 0; primes[j] <= N / i; j++) {
    //         st[primes[j] * i] = true;
    //         if (i % primes[j] == 0) break;
    //     }
    // }
    // #pragma omp parallel
    //     {
    //         int id = omp_get_thread_num();
    //         if (id == 0) nthread = omp_get_num_threads();
    // 		int cnt = 0;

    //         for (int i = id; i < N; i += nthread) {
    //             if (i % 2 == 0) continue;
    //             if (check1(i)){
    // 				cnt++;
    // 			}
    //         }
    // 		#pragma omp atomic
    //             count+=cnt;
    //     }
    for (int i = 2; i <= N; i++) {
        if (!st[i]) {
            cnt++;
        }
    }
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    printf("%d\n", cnt);
}
