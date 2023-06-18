#include <assert.h>
#include <omp.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
int thrd_num = 50;
void rscan(int *data, int *flag, int size) {
    if (size == 1) return;
    //vector<int> tpdata(size / 2);
    int *tpdata = new int[size / 2];
    //vector<int> tpflag(size / 2);
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
    rscan(&tpdata[0], &tpflag[0], size / 2);
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

// add your codes end

int main() {
    vector<int> data(SIZE, 1);
    vector<int> flag(SIZE, 0);
    vector<int> test(SIZE);

    srand(SIZE);
    data[0] = 0;
    flag[0] = 1;
    for (int i = 0; i < flag.size() / 12; i++) {
        int index = rand() % flag.size();
        data[index] = 0;
        flag[index] = 1;
    }
    for (int i = 0; i < data.size(); i++)
        test[i] = (flag[i] != 0) ? data[i] : test[i - 1] + data[i];

    double t = omp_get_wtime();
    // add your codes begin
    //vector<int> flag2 = flag;
    rscan(&data[0], &flag[0], SIZE);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++) assert(data[i] == test[i]);
}
