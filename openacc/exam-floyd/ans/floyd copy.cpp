// #define INF 1e7

// #include <omp.h>
// #include <openacc.h>
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <algorithm>
// using namespace std;

// inline int index(const int i, const int j) {
//   return i * SIZE + j;
// }

// // add your codes begin
// // add your codes end

// int main() {
//   const int size2 = SIZE * SIZE;
//   float* data = new float[size2];
//   for (int i = 0; i < size2; i++) data[i] = -INF;

//   srand(SIZE);
//   for (int i = 0; i < SIZE*20; i++) {
//     int prev = rand() % SIZE;
//     int next = rand() % SIZE;
//     if ((prev == next) || (data[index(prev, next)] > -INF)) {
//       i--;
//       continue;
//     }
//     data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
//   }

//   double t = omp_get_wtime();
//   // add your codes begin
//   // add your codes end
//   t = omp_get_wtime() - t;
//   printf("time %f %d\n", t, SIZE);

//   for (int i = 0; i < 20; i++) {
//     int prev = rand() % SIZE;
//     int next = rand() % SIZE;
//     if (prev == next) {
//       i--;
//       continue;
//     }
//     printf("test %d %d %f\n", prev, next, data[index(prev, next)]);
//   }
// }

// #define INF 1e7
// #include <assert.h>
// #include <math.h>
// #include <omp.h>
// #include <openacc.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include <algorithm>
// using namespace std;

// inline int index(const int i, const int j) { return i * SIZE + j; }

// // add your codes begin
// #define processor 8
// // add your codes end

// int main() {
//     const int size2 = SIZE * SIZE;
//     float *data = new float[size2];
//     for (int i = 0; i < size2; i++) data[i] = -INF;

//     srand(SIZE);
//     for (int i = 0; i < SIZE * 20; i++) {
//         int prev = rand() % SIZE;
//         int next = rand() % SIZE;
//         if ((prev == next) || (data[index(prev, next)] > -INF)) {
//             i--;
//             continue;
//         }
//         data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
//     }

//     double t = omp_get_wtime();
//     // add your codes begin
//     int blocksize = SIZE / processor;
//     omp_set_num_threads(processor);
//     for (int k = 0; k < SIZE; k++) {
// #pragma omp parallel num_threads(8)
//         {
//             int my_gpu = omp_get_thread_num();
//             acc_set_device_num(my_gpu, acc_device_nvidia);
// #pragma acc data copyin(data[0 : size2])
//             {
//                 int block = my_gpu;
//                 int istart = block * blocksize;
//                 int iend = istart + blocksize;
// #pragma acc parallel loop gang worker num_workers(4) vector_length(128) \
//     async(block)
//                 for (int i = istart; i < iend; i++) {
// #pragma acc loop vector
//                     for (int j = 0; j < SIZE; j++) {
//                         if (data[index(i, j)] <
//                             data[index(i, k)] + data[index(k, j)]) {
//                             data[index(i, j)] =
//                                 data[index(i, k)] + data[index(k, j)];
//                         }
//                     }
//                 }
// #pragma acc update self(data[istart * SIZE : SIZE * blocksize]) async(block)
// #pragma acc wait
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

// #define INF 1e7
// #include <assert.h>
// #include <math.h>
// #include <omp.h>
// #include <openacc.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include <algorithm>
// using namespace std;

// inline int index(const int i, const int j) { return i * SIZE + j; }

// // add your codes begin
// #define processor 4
// // add your codes end

// int main() {
//     const int size2 = SIZE * SIZE;
//     float *data = new float[size2];
//     for (int i = 0; i < size2; i++) data[i] = -INF;

//     srand(SIZE);
//     for (int i = 0; i < SIZE * 20; i++) {
//         int prev = rand() % SIZE;
//         int next = rand() % SIZE;
//         if ((prev == next) || (data[index(prev, next)] > -INF)) {
//             i--;
//             continue;
//         }
//         data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
//     }

//     double t = omp_get_wtime();
//     // add your codes begin
//     int blocksize = SIZE / processor;
//     omp_set_num_threads(processor);
// #pragma omp parallel num_threads(8)
//     {
//         for (int k = 0; k < SIZE; k++) {
//             int my_gpu = omp_get_thread_num();
//             acc_set_device_num(my_gpu, acc_device_nvidia);
// #pragma acc data copyin(data[0 : size2])  // 不能使用copy
//             {
//                 int queue = 1;
// #pragma omp for schedule(static, 1) firstprivate(queue)
//                 for (int block = 0; block < processor; block++) {
//                     int istart = block * blocksize;
//                     int iend = istart + blocksize;

// #pragma acc parallel loop async(queue)
//                     for (int i = istart; i < iend; i++) {
//                         float tmp;
//                         for (int j = 0; j < SIZE; j++) {
//                             tmp = data[index(i, k)] + data[index(k, j)];
//                             if (data[index(i, j)] < tmp) {
//                                 data[index(i, j)] = tmp;
//                             }
//                         }
//                     }
// #pragma acc update self(data[istart * SIZE : SIZE * blocksize]) async(queue)
//                     queue = queue % 2 + 1;
//                 }
// #pragma acc wait
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

#define INF 1e7

#include <assert.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
using namespace std;
// #define SIZE 1000
inline int index(const int i, const int j) { return i * SIZE + j; }

// add your codes begin

// add your codes end

int main() {
    const int size2 = SIZE * SIZE;
    float* data = new float[size2];
    for (int i = 0; i < size2; i++) data[i] = -INF;

    srand(SIZE);
    for (int i = 0; i < SIZE * 20; i++) {
        // 第一维坐标
        int prev = rand() % SIZE;
        // 第二维坐标
        int next = rand() % SIZE;
        // 如果为对称轴，或者已经被设置边权了
        if ((prev == next) || (data[index(prev, next)] > -INF)) {
            i--;
            continue;
        }
        // 赋值
        data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
    }
    double t = omp_get_wtime();

// add your codes begin
#pragma acc data copy(data[0 : size2])
    for (int k = 0; k < SIZE; k++) {
#pragma acc parallel loop gang worker num_workers(4) vector_length(128)
        for (int i = 0; i < SIZE; i++) {
            float tmp;
#pragma acc loop vector
            for (int j = 0; j < SIZE; j++) {
                tmp = data[index(i, k)] + data[index(k, j)];
                if (data[index(i, j)] < tmp) {
                    data[index(i, j)] = tmp;
                }
            }
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
