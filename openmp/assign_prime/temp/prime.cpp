// // student name:
// // id number:

// #include <math.h>
// #include <omp.h>
// #include <stdlib.h>

// #include <algorithm>
// #include <iostream>
// #include <vector>
// using namespace std;

// // add your codes begin

// // #define SIZE 100000000

// int cnt;
// bool st[SIZE];
// bool is_prime[SIZE];

// // add your codes end

// int main() {
//     vector<long> prime;

//     double t = omp_get_wtime();
//     omp_set_num_threads(25);
//     // add your codes begin
//     // 普通筛法
//     // for (int i = 2; i < SIZE; i++) {
//     //     if (!st[i]) prime.push_back(i);

//     //     for (int j = i; j < SIZE; j += i) {
//     //         if (!st[j]) st[j] = true;
//     //     }
//     // }

//     // 数理推导
// //     for (int i = 2; i * i <= SIZE; i++) {
// // // if (!st[i]) prime.push_back(i);
// // #pragma omp paraller for
// //         for (int j = i + i; j <= SIZE; j += i) {
// //             if (st[j] == 0) st[j] = 1;
// //         }
// //     }

//     for (long i = 2; i * i <= SIZE; i++) {
// #pragma omp parallel for
//         for (int j = i * i; j <= SIZE; j = j + i) {
//             if (st[j] == 0) st[j] = 1;
//         }
//     }

//     // 埃式筛法
//     // for (int i = 2; i <= SIZE; i++) {
//     //     if (!st[i]) {
//     //         // prime.push_back(i);
//     //         #pragma omp parallel for
//     //         for (int j = i; j < SIZE; j += i) {
//     //             if (!st[j]) st[j] = true;
//     //         }
//     //     }
//     // }
//     // 线性筛法
//     // for (int i = 2; i < SIZE; i++) {
//     //     if (!st[i]) {
//     //         prime.push_back(i);
//     //     }
//     //     for (int j = 0; prime[j] * i < SIZE && j < prime.size(); j++) {
//     //         st[prime[j] * i] = true;
//     //         if (i % prime[j] == 0) break;
//     //     }
//     // }

//     // add your codes end
//     t = omp_get_wtime() - t;
//     printf("time %f %ld\n", t, long(SIZE));

//     printf("prime");
//     sort(prime.begin(), prime.end());
//     // for (long i = 0; i < prime.size(); i++) printf(" %ld", prime[i]);
//     printf("\nsize %ld\n", prime.size());
// }
// student name:颜恺楠
// id number:202000130203

#include <math.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
// add your codes end
bool check[SIZE + 1];

int main() {
    vector<long> prime;

    double t = omp_get_wtime();

    // add your codes begin
    // vector<int> check(SIZE + 1, 0);
    for (long i = 2; i * i <= SIZE; i++) {
        // if (check[i] != 0 || i&1==0 || (i%6!=1 && i%6!=5))
        /* if (check[i] != 0)
          continue; */
        if (!check[i])  //! check[i]==0表示是素数
        {
// prime.push_back(i);
#pragma parallel omp for
            for (long j = i + i; j <= SIZE; j += i)
                if (!check[j]) check[j] = 1;
        }
    }
    // #pragma parallel omp for
    for (long i = 2; i <= SIZE; i++)
        if (!check[i]) prime.push_back(i);
    // add your codes end

    t = omp_get_wtime() - t;
    printf("time %f %ld\n", t, long(SIZE));

    printf("prime");
    sort(prime.begin(), prime.end());
    // for (long i = 0; i < prime.size(); i++)
    //   printf(" %ld", prime[i]);
    printf("\nsize %ld\n", prime.size());
}
