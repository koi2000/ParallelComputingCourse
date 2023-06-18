#define INF 1e7

#include <assert.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
using namespace std;

inline int index(const int i, const int j) { return i * SIZE + j; }

// add your codes begin
// add your codes end

int main() {
    const int size2 = SIZE * SIZE;
    float* data = new float[size2];
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
    int b = SIZE / 4;
    int p = 1;
#pragma acc data copy(data[0 : size2])
    for (int k = p * b; k < (p + 1) * b; k++) {
#pragma acc parallel loop gang worker num_workers(4) vector_length(128)
        for (int i = p * b; i < (p + 1) * b; i++) {
#pragma acc loop vector
            for (int j = p * b; j < (p + 1) * b; j++) {
                if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                    data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
                }
            }
        }
    }

#pragma omp parallel num_threads(2)
    {
        int my_gpu = omp_get_thread_num();
        acc_set_device_num(my_gpu, acc_device_nvidia);
#pragma acc data copyin(data[0 : size2])
        {
            for (int k = p * b; k < (p + 1) * b; k++) {
                for (int i = p * b; i < (p + 1) * b; i++) {
                    if (my_gpu == 0) {
                        for (int j = 0; j < p * b; j++) {
                            if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                                data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
                            }
                        }
                    } else {
                        for (int j = (p + 1) * b; j < SIZE; j++) {
                            if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                                data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
                            }
                        }
                    }
                }
            }
            if (my_gpu==0) {
                #pragma acc update self(data[p * b * SIZE : SIZE * b])
            }else{
                #pragma acc update self(data[st * SIZE : SIZE * blocksize])
            }
            
        }
    }

    for (int k = p * b; k < (p + 1) * b; k++) {
        for (int i = p * b; i < (p + 1) * b; i++) {
            for (int j = 0; j < p * b; j++) {
                if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                    data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
                }
            }
            for (int j = (p + 1) * b; j < SIZE; j++) {
                if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                    data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
                }
            }
        }

        for (int j = p * b; j < (p + 1) * b; j++) {
            for (int i = 0; i < p * b; i++) {
                if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                    data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
                }
            }

            for (int i = (p + 1) * b; i < SIZE; i++) {
                if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                    data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
                }
            }
        }
    }
    vector<int> arr;
    for (int i = 0; i < p * b; i++) {
        arr.push_back(i);
    }
    for (int i = (p + 1) * b; i < SIZE; i++) {
        arr.push_back(i);
    }

    int len = arr.size();

    for (int k = p * b; k < (p + 1) * b; k++) {
        for (int i : arr) {
            for (int j : arr) {
                if (data[index(i, j)] < data[index(i, k)] + data[index(k, j)]) {
                    data[index(i, j)] = data[index(i, k)] + data[index(k, j)];
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
