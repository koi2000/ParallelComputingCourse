#include <assert.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
#define CUTOFF 256
#define SIZE 100000000
static int p[6] = {0, 8, 16, 24, 32, 40};

inline int get_digit(int n, int i) { return (n >> p[i]) & (CUTOFF - 1); }

void SCAN(int* arr, int steps, int start_index) {
    if (256 < start_index) {
        return;
    } else {
#pragma acc data copy(arr [0:CUTOFF])
        {
#pragma acc parallel loop
            for (int i = start_index + (steps / 2); i < CUTOFF; i += steps) {
                arr[i] += arr[i - steps / 2];
            }
        }
        SCAN(arr, steps * 2, start_index + steps / 2);
#pragma acc data copy(arr [0:CUTOFF])
        {
#pragma acc parallel loop
            for (int i = start_index + steps; i < CUTOFF; i += steps) {
                arr[i] += arr[i - steps / 2];
            }
        }
    }
}

void quciksort(int* arr) {
    // 开了一个大小为4*SIZE的桶
    int* bucket = (int*)malloc(sizeof(int) * SIZE);
    // 开一个256大小的数组
    int count[CUTOFF];
    // 计算可能用到的最大bit数
    int cut = int(log2(10 * SIZE)) / 8 + 1;
    // cut 大小应该是5
    for (int i = 0; i < cut; i++) {
        memset(count, 0, sizeof(int) * CUTOFF);
        int sub_count[CUTOFF] = {0};
        // 获得每一位的位数数量
        // 准确来说应该是8位
        // 统计每一批 的8位位数
        for (int j = 0; j < SIZE; j += 1) {
            sub_count[get_digit(arr[j], i)]++;
        }
        for (int k = 0; k < CUTOFF; k++) {
            count[k] += sub_count[k];
        }
        SCAN(count, 2, 0);
        for (int j = SIZE - 1; j >= 0; --j) {
            int k = get_digit(arr[j], i);
            bucket[count[k] - 1] = arr[j];
            count[k]--;
        }
        memcpy(arr, bucket, sizeof(int) * SIZE);
    }
    free(bucket);
}
// add your codes end

int main() {
    vector<int> data(SIZE);

    srand(SIZE);
    for (int i = 0; i < SIZE; i++) data[i] = rand() % (SIZE * 10);

    double t = omp_get_wtime();
    // add your codes begin
    quciksort(&data[0]);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE - 1; i++) assert(data[i] <= data[i + 1]);
}