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
const int thrd_num = 30;

void rscan(vector<int> &data, int size) {
    if (size == 1) return;
    vector<int> twoSum(size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < twoSum.size(); i++) {
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