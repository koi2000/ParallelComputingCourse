#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define ll long long
using namespace std;

// add your codes begin
#define SIZE 100000000
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
    int* piv = new int[p - 1];
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
// add your codes end

int main() {
    // 首先需要构造出有环的array pool
    vector<int> data(SIZE, -1);
    vector<int> prev(SIZE, -1);
    vector<int> next(SIZE, -1);
    int circlenum = 19;
    int listnum = 3;
    vector<vector<int>> circles1(circlenum);
    vector<vector<int>> circles2(listnum);
    srand(SIZE);
    {
        int sizes1[] = {17, 28, 94, 21, 46, 21, 28, 94, 670, 1230, 1236, 88763, 3674, 2561, 271, 391, 998, 2613, 275634};
        // int sizes1[] = {17, 28, 94, 21, 46, 21, 28, 94, 670, 1230, 1236, 88763, 3674, 2561, 271, 391, 998, 2613, 275634};
        int sizes2[] = {23, 68, 47};
        set<int> st;
        for (int i = 0; i < circlenum; i++) {
            for (int j = 0; j < sizes1[i]; j++) {
                int idx = rand() % SIZE;
                if (st.count(idx)) {
                    j--;
                    continue;
                } else {
                    circles1[i].push_back(idx);
                    st.insert(idx);
                }
            }
        }
        for (int i = 0; i < circlenum; i++) {
            for (int j = 0; j < circles1[i].size() - 1; j++) {
                prev[circles1[i][j]] = circles1[i][j + 1];
            }
            for (int j = 1; j < circles1[i].size(); j++) {
                next[circles1[i][j]] = circles1[i][j - 1];
            }
            prev[circles1[i][sizes1[i] - 1]] = circles1[i][0];
            next[circles1[i][0]] = circles1[i][sizes1[i] - 1];
        }

        for (int i = 0; i < listnum; i++) {
            for (int j = 0; j < sizes2[i]; j++) {
                int idx = rand() % SIZE;
                if (st.count(idx)) {
                    j--;
                    continue;
                } else {
                    circles2[i].push_back(idx);
                    st.insert(idx);
                }
            }
        }
        for (int i = 0; i < listnum; i++) {
            for (int j = 0; j < circles2[i].size() - 1; j++) {
                prev[circles2[i][j]] = circles2[i][j + 1];
            }
        }
    }
    double t = omp_get_wtime();
    // add your codes begin

    vector<int> flag(SIZE);
#pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        flag[i] = i;
    }

    int* cflag = new int[SIZE];
    int* cprev = new int[SIZE];
    for (int i = 0; pow(2, i) < SIZE; i++) {
        int step = pow(2, i);
#pragma omp parallel for
        for (int i = 0; i < SIZE; i++) cflag[i] = flag[i];
#pragma omp parallel for
        for (int i = 0; i < SIZE; i++) cprev[i] = prev[i];
#pragma omp parallel for
        for (int j = 0; j < SIZE; j++) {
            if (prev[j] != -1) {
                flag[j] = max(cflag[prev[j]], flag[j]);
                prev[j] = cprev[prev[j]];
            }
        }
    }
    //     sampleSort(flag, SIZE, 50, 500);
    //     int* diff = new int[SIZE];
    //     diff[0] = flag[0];
    //     #pragma omp parallel for
    //     for (int i = 1; i < SIZE; i++) {
    //         diff[i] = flag[i] - flag[i - 1];
    //     }
    //     int res = 0;
    //     #pragma omp parallel for
    //     for (int i = 0; i < SIZE; i++) {
    //         if (diff[i] > 0) {
    // #pragma omp atomic
    //             res++;
    //         }
    //     }
    //     cout<<res<<endl;
    set<int> st;
#pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        // 首先判断是否出现了环
        if (prev[i] != -1) {
#pragma omp critical
            // 根据唯一标识检测环的数量
            if (!st.count(flag[i])) {
                st.insert(flag[i]);
            }
        }
    }
    int res = st.size();

    //  add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);
    assert(res == circlenum);
}
