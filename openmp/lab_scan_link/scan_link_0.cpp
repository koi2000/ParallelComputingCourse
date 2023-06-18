// student name: 宋家庆
// id number:202000130061

#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
// #define SIZE 1000
// add your codes end

int main() {
    vector<int> data(SIZE, -1);
    vector<int> prev(SIZE, -1);
    vector<int> next(SIZE, -1);
    vector<int> test(SIZE, -1);

    srand(SIZE);
    {
        int tmp = -1;
        for (int i = 0; i < SIZE / 2; i++) {
            int idx = rand() % SIZE;
            while (data[idx] >= 0) idx = (idx + 1) % SIZE;
            if (i > 0) {
                data[idx] = 1;
                prev[idx] = tmp;
                next[tmp] = idx;
            } else {
                data[idx] = 0;
            }
            test[idx] = i;
            tmp = idx;
        }
    }

    double t = omp_get_wtime();
    // add your codes begin
    // 将data的初始值全部置为0
#pragma omp parallel for
    for (int i = 0; i < SIZE; i++)
        if (data[i] == 1) data[i] = 0;0

    int* cdata = new int[SIZE];
    int* cprev = new int[SIZE];
    // vector<int> cdata(SIZE, -1);
    // vector<int> cprev(SIZE, -1);
    for (int i = 0; pow(2, i) < SIZE; i++) {
        int step = pow(2, i);
        // memcpy(&cdata[0], &data[0], 4*SIZE);
        // memcpy(&cprev[0], &prev[0], 4*SIZE);
#pragma omp parallel for
        for (int i = 0; i < SIZE; i++) cdata[i] = data[i];
#pragma omp parallel for
        for (int i = 0; i < SIZE; i++) cprev[i] = prev[i];
#pragma omp parallel for
        for (int j = 0; j < SIZE; j++) {
            if (prev[j] != -1) {
                data[j] = cdata[prev[j]] + step;
                prev[j] = cprev[prev[j]];
            }
        }
    }
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++) assert(data[i] == test[i]);
}
