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
#pragma omp parallel num_threads(8)
    {
        int id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        acc_set_device_num(id, acc_device_nvidia);
#pragma acc data copy(data[0 : size2])
        for (int k = id; k < SIZE; k += nthrds) {
#pragma acc parallel loop gang worker num_workers(4) vector_length(256) //async(id)
            for (int i = 0; i < SIZE; i++) {
#pragma acc loop vector
                for (int j = 0; j < SIZE; j++) {
                    float temp = data[index(i, k)] + data[index(k, j)];
                    if (data[index(i, j)] < temp) {
                        data[index(i, j)] = temp;
                    }
                }
            }
        }
#pragma acc update device(imgData[starty*step:blocksize*step])
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
