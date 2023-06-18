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
const int thrds = 30;
// #define SIZE 1000
int results[SIZE];
// add your codes end

void sampleSort(vector<int>& data, int n, int p, int s) {
    int* sample = new int[p * s];
    // 采样
#pragma omp parallel for
    for (int i = 0; i < p * s; i++) {
        sample[i] = data[rand() % n];
    }
    omp_set_nested(1);
    // 对采样结果进行排序
    sort(sample, sample + p * s);
    // 选出若干个pivots
    int* piv = new int[p-1];
    for (int i = 0; i < p - 1; i++) {
        piv[i] = sample[(i + 1) * s];
    }
    // 对每个段打flag并记录其位置
    vector<int> offsets(p, 0);
    int* flags = new int[n];
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p - 1; j++) {
            if (data[i] > piv[j]) {
                flags[i]++;
            } else {
                break;
            }
        }
#pragma omp atomic
        offsets[flags[i]]++;
    }
    // 记录每个flag对应的在总数组中的位置
    offsets.insert(offsets.begin(), 0);
    int sum = 0;
    for (int i = 1; i < offsets.size(); i++) {
        sum += offsets[i];
        offsets[i] = sum;
    }
    // 这里是compact，找一种合适的方法进行compact
    int* tmp = new int[n];
#pragma omp parallel num_threads(p)
    {
        int id, i, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        // 每个线程只执行循环中自己需要执行的部分
        vector<int> tp;
        // for (i = id; i < p; i += nthrds) {
        for (int j = 0; j < n; j++) {
            if (flags[j] == id) {
                tp.push_back(flags[j]);
            }
        }
#pragma omp critical
        {
            memcpy(&tmp[offsets[id]], &tp[0], 4 * tp.size());
            offsets[id] += tp.size();
        }
        // }
    }
    // 对每个块执行最快的串行排序算法
    offsets.insert(offsets.begin(), 0);
#pragma omp parallel for num_threads(p)
    for (int i = 0; i < p; i++) {
        sort(tmp + offsets[i], tmp + offsets[i + 1]);
    }
    memcpy(&data[0], &tmp[0], sizeof(int) * SIZE);
}

int main() {
    vector<int> data(SIZE);
    srand(SIZE);
    for (int i = 0; i < SIZE; i++) data[i] = rand() % (SIZE * 10);

    double t = omp_get_wtime();
    // add your codes begin
    // int n = SIZE;
    // // 得到k的最大取值
    // int k = SIZE / thrds;
    // // 采样的总数量最少为 p-1 个
    // // 随机选取一个k值，表示采样的总数量
    // int samples = thrds * abs(rand() % k);
    // // 从原数组中筛选出samples个数

    // for (int i = 0; i < samples; i++) {
    //     // 取出一个随机数
    //     int r = (int)(rand() % n);
    //     results[i] = data[r];
    //     // 排除已经取过的值
    //     data[r] = data[n - 1];
    //     n--;
    // }
    // // 对这些数进行排序
    // sort(results, results + samples);
    // // 从其中选出thrd-1个点，将元素组变为thrd个段
    // vector<int> p;
    // for (int i = thrds; i < samples; i += thrds) {
    //     p.push_back(results[i]);
    // }
    // // 对这些段打flag
    // vector<int> flag(SIZE, 0);
    // int maxx = -1;
    // for (int i = 0; i < p.size(); i++) {
    //     for (int j = 0; j < data.size(); j++) {
    //         if (data[j] >= p[i]) {
    //             flag[j]++;
    //             maxx = max(maxx, flag[j]);
    //         }
    //     }
    // }
    // maxx++;
    // vector<vector<int>> coms(maxx, vector<int>());
    // // 执行compact，选出来每一个段
    // for (int i = 0; i < SIZE; i++) {
    //     coms[flag[i]].push_back(data[i]);
    // }
    // for (int i = 0; i < maxx; i++) {
    //     sort(coms[i].begin(), coms[i].end());
    // }
    // // 对每个段执行最快的串行排序算法

    // // 汇总得到结果
    // data.resize(0);
    // for (int i = 0; i < maxx; i++) {
    //     for (int j = 0; j < coms[i].size(); j++) {
    //         data.push_back(coms[i][j]);
    //     }
    // }
    sampleSort(data, SIZE, 50, 500);
    // sampleSort(data, SIZE, 30, 500);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE - 1; i++) assert(data[i] <= data[i + 1]);
}
