// student name:
// id number:

#include <assert.h>
#include <omp.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
using namespace std;

// add your codes begin
// #define SIZE 1000
// add your codes end

int main() {
    vector<int> data(SIZE, 1);
    data[0] = 0;

    double t = omp_get_wtime();
    omp_set_num_threads(100);
    // add your codes begin
    vector<int> temp = data;
    omp_set_nested(1);
#pragma omp paraller num_threads(30)
    {
        int id, i, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        int num = SIZE;
        for (i = id; i < SIZE; i += nthrds) {
            int sum = 0;
//#pragma omp parallel for num_threads(30)
            for (int j = 0; j <= i; j++) {
//#pragma omp atomic
                sum += temp[j];
            }
            data[i] = sum;
        }
    }
// #pragma omp parallel for num_threads(30)
//     for (int i = 2; i < SIZE; i++) {
// #pragma omp parallel for num_threads(30)
//         for (int j = i; j < SIZE; j++) {
//             #pragma omp atomic
//             data[j] += temp[i];
//         }
//     }
    // for (int i = 0; i < SIZE; i++) {
    //     cout<<data[i]<<endl;
    // }
    

    //     for (int i = 1; i < SIZE; i++) {
    //         int res = 0;
    //         for (int j = 1; j <= i; j++) {
    //             res += data[j];
    //         }
    // #pragma omp critical
    //         data[i] = res;
    //     }
    // data = temp;

    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++) assert(data[i] == i);
}
