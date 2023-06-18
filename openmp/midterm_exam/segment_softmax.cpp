#include <assert.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
#define SIZE 100000000

int thrd_num = 60;
void seg_scan(double *data, int *flag, int size) {
    if (size == 1) return;
    double *tpdata = new double[size / 2];

    int *tpflag = new int[size / 2];
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < size / 2; i++) {
        if (flag[2 * i + 1] == 1) {
            tpdata[i] = data[2 * i + 1];
            tpflag[i] = flag[2 * i + 1];
        } else {
            tpdata[i] = data[i * 2] + data[2 * i + 1];
            tpflag[i] = flag[2 * i] | flag[2 * i + 1];
        }
    }
    seg_scan(&tpdata[0], &tpflag[0], size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 1; i < size; i += 2) {
        data[i] = tpdata[i / 2];
        if (i + 1 < size) {
            if (flag[i + 1] != 1) {
                data[i + 1] = tpdata[(i + 1) / 2 - 1] + data[i + 1];
                flag[i + 1] = flag[i + 1] | tpflag[(i + 1) / 2 - 1];
            }
        }
    }
}

void scan(vector<int> &data, int size) {
    if (size == 1) return;
    vector<int> twoSum(size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < twoSum.size(); i++) {
        twoSum[i] = data[i * 2] + data[2 * i + 1];
    }
    scan(twoSum, size / 2);
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
    // 首先构造出测试的环境
    // 一个data数组，存储待segment softmax的数字
    // 一个flag数组，存储segment标记
    // 一个test数组，存出正确的结果，用于答案比对
    vector<double> data(SIZE, 0);
    vector<int> flag(SIZE, 0);
    vector<double> test(SIZE);

    srand(SIZE);
    flag[0] = 1;
    int cnt = 0;
    while (true) {
        // 计算这一次所需要的长度
        int len = rand() % 10 + 1;
        if (len + cnt > SIZE) {
            len = SIZE - cnt;
        }
        // test数组先附上对应的值
        vector<double> arr(len);
        double sum = 0;
        for (int i = 0; i < len; i++) {
            arr[i] = rand() % 10 + 1;
            test[i + cnt] = exp(arr[i]);
            sum += test[i + cnt];
        }
        // 转为对应的softmax值
        for (int i = cnt; i < cnt + len; i++) {
            test[i] /= sum;
            data[i] = arr[i - cnt];
        }
        cnt += len;
        if (cnt == SIZE) break;
        flag[cnt] = 1;
    }
    double t = omp_get_wtime();
    // add your codes begin
    // 先直接对所有原数据求exp
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < SIZE; i++) {
        data[i] = exp(data[i]);
    }
    vector<double> datas = vector(data.begin(), data.end());
    vector<int> flags = vector(flag.begin(), flag.end());
    vector<int> tpflags = vector(flag.begin(), flag.end());
    // 执行并行的segment_scan算法，求每个区间的前缀和
    seg_scan(&datas[0], &tpflags[0], SIZE);
    // 对flag数组执行并行的scan算法，方便获取每个数字对应的前缀和的下标
    scan(flags, SIZE);

    vector<double> sums(flags[flags.size() - 1] + 1);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 1; i < SIZE; i++) {
        if (flag[i]) {
            sums[flags[i] - 1] = datas[i - 1];
        }
    }
    sums.erase(sums.begin());
    sums[sums.size() - 1] = datas[SIZE - 1];

#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < SIZE; i++) {
        double re = sums[flags[i] - 1];
        data[i] = data[i] / re;
    }

    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++) assert(abs(data[i] - test[i]) < 1e-7);
}
