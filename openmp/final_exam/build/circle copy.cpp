#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#define ll long long
using namespace std;

// add your codes begin
#define SIZE 10000

// add your codes end

int main() {
    // 首先需要构造出有环的array pool
    vector<int> data(SIZE, -1);
    vector<int> prev(SIZE, -1);
    int circlenum = 8;
    int listnum = 3;
    vector<vector<int>> circles1(circlenum);
    vector<vector<int>> circles2(listnum);
    srand(SIZE);
    {
        int sizes1[] = {17, 28, 94, 21, 46, 21, 28, 94};
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
            prev[circles1[i][sizes1[i] - 1]] = circles1[i][0];
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

    // 记录每个节点的前驱节点，用于判断是否成环
    int* sprev = new int[SIZE];
    // vector<int> sprev(SIZE);
// #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        // 为每个节点赋予不同的值，方便找到哪些节点属于同一个环
        data[i] = i;
        sprev[i] = prev[i];
    }
    int* cdata = new int[SIZE];
    int* cprev = new int[SIZE];
//     for (int i = 0; i < SIZE; i++) {
//         // 提前复制一份，防止既读又写影响答案正确性
// #pragma omp parallel for
//         for (int i = 0; i < SIZE; i++) cdata[i] = data[i];
// #pragma omp parallel for
//         for (int i = 0; i < SIZE; i++) cprev[i] = prev[i];
// #pragma omp parallel for
//         for (int j = 0; j < SIZE; j++) {
//             // 如果已经检测到该结点在某一环内，则直接停止
//             if (prev[j] == -2) continue;
//             // 如果该结点没有走到根节点且暂时未检测到属于某一环
//             if (prev[j] != -1) {
//                 // data[i]加上前缀节点的data值
//                 data[j] += cprev[j];
//                 // 前缀节点指向前缀节点的前缀节点
//                 prev[j] = sprev[prev[j]];
//                 // 如果发现与prev数组的初始值相同，说明检测到了环
//                 // 当存在环，每个点的前缀节点在每一次迭代中都会更新为其前缀时，需要n步即可走回原节点，n为环中节点数量
//                 if (prev[j] == sprev[j]) {
//                     // 更新为已检测到环
//                     prev[j] = -2;
//                     // data数组乘上检测到环所需要的步数，环中所有节点该值都相同
//                     // 且由于data数组每个元素值都不相同，不存在其他的环，其环中所有节点的和乘上环的大小的值与该环相同
//                     // 该值可以唯一的标识一个环
//                     data[j] -= cprev[j];
//                     data[j] *= i;
//                 }
//             }
//         }
//     }
//     set<int> st;
// #pragma omp parallel for
//     for (int i = 0; i < SIZE; i++) {
//         // 首先判断是否出现了环
//         if (prev[i] == -2) {
// #pragma omp critical
//             // 根据唯一标识检测环的数量
//             if (!st.count(data[i])) {
//                 st.insert(data[i]);
//             }
//         }
//     }
//     int res = st.size();

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
    int res = 0;
    //  add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);
    assert(res == circlenum);
}
