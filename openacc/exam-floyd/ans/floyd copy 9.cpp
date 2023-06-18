#define INF 1e7
// #pragma GCC optimize(3)
#include <assert.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <vector>
using namespace std;
#define SIZE 6000
inline int index(const int i, const int j) { return i * SIZE + j; }

// add your codes begin

// add your codes end

int main() {
    const int size2 = SIZE * SIZE;
    float *data = new float[size2];
    for (int i = 0; i < size2; i++) data[i] = -INF;

    srand(SIZE);
    for (int i = 0; i < SIZE * 20; i++) {
        int prev = rand() % SIZE;
        int next = rand() % SIZE;
        if ((prev == next) || (data[index(prev, next)] > -INF)) {
            i--;
            continue;
        }
        data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
    }

    double t = omp_get_wtime();
    // add your codes begin
    int b = SIZE / 150;
#pragma acc data copy(data[0 : size2])
    {
        for (int p = 0; p < 150; p++) {
            for (int k = p * b; k < (p + 1) * b; k++) {
#pragma acc parallel loop gang worker num_workers(4) vector_length(128)
                for (int i = p * b; i < (p + 1) * b ; i++) {
#pragma acc loop vector
                    for (int j = p * b; j < (p + 1) * b; j++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
                }
            }

            for (int k = p * b; k < (p + 1) * b; k++) {
#pragma acc parallel loop gang worker num_workers(4) vector_length(128) async(1 + k)
                for (int i = p * b; i < (p + 1) * b; i++) {
#pragma acc loop vector
                    for (int j = 0; j < p * b; j++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
#pragma acc loop vector
                    for (int j = (p + 1) * b; j < SIZE; j++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
                }
#pragma acc parallel loop gang worker num_workers(4) vector_length(128) async(2 + k)
                for (int j = p * b; j < (p + 1) * b; j++) {
#pragma acc loop vector
                    for (int i = 0; i < p * b; i++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
#pragma acc loop vector
                    for (int i = (p + 1) * b; i < SIZE; i++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
                }
            }

#pragma acc wait
            for (int k = p * b; k < (p + 1) * b; k++) {
#pragma acc parallel loop gang worker num_workers(2) vector_length(128) async(1 + k)
                for (int i = 0; i < p * b; i++) {
#pragma acc loop vector
                    for (int j = 0; j < p * b; j++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
                }

#pragma acc parallel loop gang worker num_workers(4) vector_length(128) async(2 + k)
                for (int i = 0; i < p * b; i++) {
#pragma acc loop vector
                    for (int j = (p + 1) * b; j < SIZE; j++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
                }
#pragma acc parallel loop gang worker num_workers(8) vector_length(128) async(3 + k)
                for (int i = (p + 1) * b; i < SIZE; i++) {
#pragma acc loop vector
                    for (int j = 0; j < p * b; j++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
                }
#pragma acc parallel loop gang worker num_workers(8) vector_length(128) async(4 + k)
                for (int i = (p + 1) * b; i < SIZE; i++) {
#pragma acc loop vector
                    for (int j = (p + 1) * b; j < SIZE; j++) {
                        float tp = data[i * SIZE + k] + data[k * SIZE + j];
                        if (data[i * SIZE + j] >= tp) continue;
                        data[i * SIZE + j] = tp;
                    }
                }
            }
#pragma acc wait
        }
    }

    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < 20; i++) {
        int prev = rand() % SIZE;
        int next = rand() % SIZE;
        if (prev == next) {
            i--;
            continue;
        }
        printf("test %d %d %f\n", prev, next, data[index(prev, next)]);
    }
}
// #define INF 1e7

// #include <assert.h>
// #include <math.h>
// #include <omp.h>
// #include <openacc.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include <algorithm>
// using namespace std;
// // #define SIZE 1000
// inline int index(const int i, const int j) { return i * SIZE + j; }

// // add your codes begin

// // add your codes end

// int main() {
//     const int size2 = SIZE * SIZE;
//     float* data = new float[size2];
//     for (int i = 0; i < size2; i++) data[i] = -INF;

//     srand(SIZE);
//     for (int i = 0; i < SIZE * 20; i++) {
//         // 第一维坐标
//         int prev = rand() % SIZE;
//         // 第二维坐标
//         int next = rand() % SIZE;
//         // 如果为对称轴，或者已经被设置边权了
//         if ((prev == next) || (data[index(prev, next)] > -INF)) {
//             i--;
//             continue;
//         }
//         // 赋值
//         data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
//     }
//     double t = omp_get_wtime();

// // add your codes begin
// #pragma acc data copy(data[0 : size2])
//     for (int k = 0; k < SIZE; k++) {
// #pragma acc parallel loop gang worker num_workers(4) vector_length(128)
//         for (int i = 0; i < SIZE; i++) {
// #pragma acc loop vector
//             for (int j = 0; j < SIZE; j++) {
//                 // if (data[index(i,j)] < data[index(i,k)] + data[index(k,j)]) {
//                 //     data[index(i,j)] = data[index(i,k)] + data[index(k,j)];
//                 // }
//                 // if (data[i * SIZE + j] >= data[i * SIZE + k] + data[k * SIZE + j]) continue;
//                 // data[i * SIZE + j] = data[i * SIZE + k] + data[k * SIZE + j];
//                 float tp = data[i * SIZE + k] + data[k * SIZE + j];
//                 if (data[i * SIZE + j] >= tp) continue;
//                 data[i * SIZE + j] = tp;
//             }
//         }
//     }

//     // add your codes end
//     t = omp_get_wtime() - t;
//     printf("time %f %d\n", t, SIZE);

//     for (int i = 0; i < 20; i++) {
//         int prev = rand() % SIZE;
//         int next = rand() % SIZE;
//         if (prev == next) {
//             i--;
//             continue;
//         }
//         printf("test %d %d %f\n", prev, next, data[index(prev, next)]);
//     }
// }
