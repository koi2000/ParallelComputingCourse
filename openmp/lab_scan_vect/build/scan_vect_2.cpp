// student name:
// id number:

#include <assert.h>
#include <omp.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
using namespace std;

// add your codes start
// #define SIZE 1000
int num_thrd = 10;
void add_sum(vector<int> &a, int n) {
    if (n == 1) return;

    vector<int> b(n / 2, 0);
#pragma omp parallel num_threads(num_thrd)
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        int start = id * n / nthrds;
        int end = (id + 1) * n / nthrds;
        if (id == nthrds - 1) {
            end = n;
        }
        for (int i = start + start % 2; i < end; i += 2) {
            b[i / 2] = a[i] + a[i + 1];
        }
    }
    add_sum(b, n / 2);

#pragma omp parallel num_threads(num_thrd)
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        int margin = n / nthrds;
        int start = id * margin;
        int end = (id + 1) * margin;
        if (id == nthrds - 1) {
            end = n;
        }
        start = max(start, 2);
        for (int i = start + start % 2; i < end; i += 2) {
            a[i] += b[i / 2 - 1];
            a[i - 1] = b[(i - 1) / 2];
        }
    }
    if ((n - 1) % 2 == 1) {
        a[n - 1] = b[(n - 1) / 2];
    }
}

const int thrd_num = 10;

vector<int> caleven(vector<int> cur) {
    vector<int> ans(cur.size() / 2);
#pragma omp parallel for
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = cur[i * 2] + cur[2 * i + 1];
    }
    return ans;
}

vector<int> recursion_scan(vector<int> &cur) {
    vector<int> res(cur.size());
    res[0] = cur[0];
    if (res.size() == 1) return res;
    vector<int> evenans = caleven(cur);
    vector<int> evenprev = recursion_scan(evenans);
#pragma omp parallel for
    for (int i = 1; i < res.size(); i++) {
        if (i & 1) {
            res[i] = evenprev[i / 2];
        } else {
            res[i] = evenprev[i / 2 - 1] + cur[i];
        }
    }
    return res;
}

void rscan(vector<int> &data, int size) {
    // vector<int> res(size);
    // res[0] = data[0];
    if (size == 1) return;
    vector<int> twoSum(size / 2);
#pragma omp parallel for
    for (int i = 0; i < twoSum.size(); i++) {
        twoSum[i] = data[i * 2] + data[2 * i + 1];
    }
    rscan(twoSum, size / 2);
#pragma omp parallel for
    for (int i = 1; i < size; i += 2) {
        data[i] = twoSum[i / 2];
        if (i + 1 < size) {
            data[i + 1] = twoSum[(i + 1) / 2 - 1] + data[i + 1];
        }
    }
}

// vector<int> rscan(vector<int> &data, int size) {
//     vector<int> res(size);
//     res[0] = data[0];
//     if (res.size() == 1) return res;
//     vector<int> twoSum(size / 2);
// #pragma omp parallel for
//     for (int i = 0; i < twoSum.size(); i++) {
//         twoSum[i] = data[i * 2] + data[2 * i + 1];
//     }
//     vector<int> tpSum = rscan(twoSum, size / 2);
// #pragma omp parallel for
//     for (int i = 1; i < res.size(); i += 2) {
//         data[i] = tpSum[i / 2];
//         data[i + 1] = tpSum[(i + 1) / 2 - 1] + data[i+1];
//         // if (i & 1) {
//         //     res[i] = tpSum[i / 2];
//         // } else {
//         //     res[i] = tpSum[i / 2 - 1] + data[i];
//         // }
//     }
//     return res;
// }

// add your codes end

int main() {
    vector<int> data(SIZE, 1);
    data[0] = 0;

    double t = omp_get_wtime();
    // add your codes start
    rscan(data, SIZE);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++) assert(data[i] == i);
}