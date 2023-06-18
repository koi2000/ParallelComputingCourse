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
const int thrd_num = 30;

void rscan(int* data, int size) {
    if (size == 1) return;
    int* twoSum = new int[size / 2];
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
//     #pragma omp barrier
    // int* vis = new int[SIZE];
    vector<int> vis(SIZE);
#pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        if (prev[i] != -1) {
            vis[flag[i]] = 1;
        } else {
            vis[i] = 0;
        }
    }
    rscan(&vis[0], SIZE);
    int res = vis[SIZE - 1];

//     set<int> st;
// #pragma omp parallel for
//     for (int i = 0; i < SIZE; i++) {
//         // 首先判断是否出现了环
//         if (prev[i] != -1) {
// #pragma omp critical
//             // 根据唯一标识检测环的数量
//             if (!st.count(flag[i])) {
//                 st.insert(flag[i]);
//             }
//         }
//     }
//     int res = st.size();

    cout << res << endl;
    //  add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);
    assert(res == circlenum);
}
