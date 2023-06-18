// student name:
// id number:

#include <assert.h>
#include <omp.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
// add your codes end

int main() {
    vector<int> data(SIZE, 1);
    data[0] = 0;

    double t = omp_get_wtime();
    // add your codes begin
    int res = 0;
    for (int i = 1; i < SIZE; i++) {
        res += data[i];
        data[i] = res;
    }

    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++) assert(data[i] == i);
}
