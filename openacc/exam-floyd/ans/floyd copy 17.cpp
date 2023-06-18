#define INF 1e7
// #pragma GCC optimize(2)
#include <assert.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
using namespace std;

inline int index(const int i, const int j) {
    return i * SIZE + j;
}

// add your codes begin
// add your codes end

int main() {
    const int size2 = SIZE * SIZE;
    float *data = new float[size2];
    for (int i = 0; i < size2; i++)
        data[i] = -INF;

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

    int processor = 3;
    int blocksize = SIZE / processor;
    float *dik = new float[SIZE];  
    float *dkj = new float[SIZE];  
#pragma omp parallel for num_threads(30)
    for (int i = 0; i < SIZE; i++)  
    {
        dik[i] = data[i * SIZE];
        dkj[i] = data[i];
    }
#pragma omp parallel num_threads(processor)
    {
        int id = omp_get_thread_num();
        acc_set_device_num(id, acc_device_nvidia);
        int begin = id * blocksize;  
        int end = begin + blocksize;
#pragma acc data copyin(data[begin * SIZE : blocksize * SIZE])  
#pragma acc data create(dik[0 : SIZE], dkj[0 : SIZE])
        {
            for (int k = 0; k < SIZE; k++) {
#pragma acc update device(dik[0 : SIZE], dkj[0 : SIZE])
#pragma acc parallel loop gang worker num_workers(1) vector_length(1024)
// #pragma acc loop tile(32)
// #pragma acc parallel loop gang
                for (int i = begin; i < end; i++)  
                {
                    //if (dik[i] == -INF) continue;
// #pragma acc loop vector    
#pragma acc loop independent                 
                    for (int j = 0; j < SIZE; j++) {
                        //if (dkj[j] == -INF) continue;
                        if (data[i * SIZE + j] >= dik[i] + dkj[j]) continue;
                        data[i * SIZE + j] = dik[i] + dkj[j];
                    }
                }
                if (k == SIZE - 1) continue;
                #pragma acc parallel loop 
                for (int i = begin; i < end; i++) {
                    dik[i] = data[i * SIZE + k + 1];
                }
                #pragma acc update self(dik[begin : blocksize]) 
                if (k + 1 >= begin && k + 1 < end) {
                    #pragma acc parallel loop 
                    for (int i = 0; i < SIZE; i++)
                        dkj[i] = data[(k + 1) * SIZE + i];
                    #pragma acc update self(dkj[0 : SIZE]) 
                }
#pragma omp barrier  
            }
#pragma acc update self(data[begin * SIZE : blocksize * SIZE])  
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
// #pragma GCC optimize(2)
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
// #pragma acc parallel loop gang worker num_workers(2) vector_length(256) //async(1)
//         for (int i = 0; i < SIZE ; i++) {
//             if (data[i * SIZE + k] == -INF) continue;
// #pragma acc loop vector
//             for (int j = 0; j < SIZE; j++) {
//                 if (data[i * SIZE + j] >= data[i * SIZE + k] + data[k * SIZE + j]) continue;
//                 data[i * SIZE + j] = data[i * SIZE + k] + data[k * SIZE + j];
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