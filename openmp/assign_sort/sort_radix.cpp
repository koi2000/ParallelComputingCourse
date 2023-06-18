// student name: 宋家庆
// id number: 202000130061

#define CUTOFF 1024

#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
#define maxbit 256
int thrd_num = 10;
int bitnum = 256;
// #define SIZE 1000
int bits[6] = {0, 8, 16, 24, 32, 40};
// int bits[12] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40};

inline int get_bit(int x, int bit) { return (x >> bits[bit]) & bitnum - 1; }

void rscan(int* data, int size) {
    if (size == 1) return;
    int twoSum[size / 2];
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < size / 2; i++) {
        twoSum[i] = data[i * 2] + data[2 * i + 1];
    }
    rscan(twoSum, size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 1; i < size; i += 2) {
        data[i] = twoSum[i / 2];
        if (i + 1 < size) {
            data[i + 1] = twoSum[(i + 1) / 2 - 1] + data[i + 1];
        }
    }
}

void bit_sort(vector<int>& data) {
    int cut = int(log2(10 * SIZE)) / 8 + 1;
    int cnt[bitnum];
    // vector<int> cnt(bitnum);
    // 开一个数组用于备份原数组
    int* bucket = (int*)malloc(sizeof(int) * SIZE);
    for (int i = 0; i < cut; i++) {
        memset(cnt, 0, sizeof cnt);
        // std::fill(cnt.begin(), cnt.end(), 0);
        // 向每个桶里放数据
        // 不需要真的把数据放进桶里
        // 记录一下每个桶里数据的数量
        for (int j = 0; j < data.size(); j++) {
            // bucket[get_bit(data[j], i)].push_back(data[j]);
            cnt[get_bit(data[j], i)]++;
        }
        // 求前缀和，得知每个数字应该放在哪个位置
        rscan(&cnt[0], bitnum);
        // cnt.insert(cnt.begin(), 0);
        // 可能存在false sharing，这部分不再并行
        // TODO: 一个compact 可以尝试一下并行
        // 似乎因为线程太多，不太可行
        // 并行compact由于需要拷贝数组，导致性能下降，不再进行并行compact
        // #pragma omp parallel num_threads(256)
        //         {
        //             int id, nthrds;
        //             id = omp_get_thread_num();
        //             // cout << id << endl;
        //             nthrds = omp_get_num_threads();
        //             // 每个线程只执行循环中自己需要执行的部分
        //             vector<int> tp;
        //             for (int j = 0; j < SIZE; j++) {
        //                 if (get_bit(data[j], i) == id) {
        //                     tp.push_back(data[j]);
        //                 }
        //             }
        // #pragma omp critical
        //             { memcpy(bucket, &tp[0], 4 * tp.size()); }
        //         }

        for (int j = SIZE - 1; j >= 0; j--) {
            int bit = get_bit(data[j], i);
            bucket[cnt[bit] - 1] = data[j];
            cnt[bit]--;
        }
        memcpy(&data[0], bucket, sizeof(int) * SIZE);
    }
}

// add your codes end

int main() {
    vector<int> data(SIZE);

    srand(SIZE);
    for (int i = 0; i < SIZE; i++) data[i] = rand() % (SIZE * 10);

    double t = omp_get_wtime();
    // add your codes begin
    bit_sort(data);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE - 1; i++) assert(data[i] <= data[i + 1]);
}
