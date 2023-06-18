#include <assert.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <vector>

#define SIZE 1000000
using namespace std;


void sampleSort(int *arr, int n, int p) {
    // Step 1: Sample data
    int s = 10 * p;  // Sample size
    int *sample = new int[s * p];
    srand(time(NULL));
#pragma omp parallel for
    for (int i = 0; i < s * p; i++) {
        sample[i] = arr[rand() % n];
    }
    std::sort(sample, sample + s * p);
    // Step 2: Choose pivots
    std::vector<double> pivots(p - 1);
    for (int i = 0; i < p - 1; i++) {
        pivots[i] = sample[(i + 1) * s];
    }

    // Step 3: Partition data
    std::vector<int> counts(p);
    std::vector<int> offsets(p);
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int rank = p - 1;
        for (int j = 0; j < p - 1; j++) {
            if (arr[i] < pivots[j]) {
                rank = j;
                break;
            }
        }
#pragma omp atomic
        counts[rank]++;
    }
    offsets[0] = 0;
    for (int i = 1; i < p; i++) {
        offsets[i] = offsets[i - 1] + counts[i - 1];
    }
    double *tmp = new double[n];
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int rank = p - 1;
        for (int j = 0; j < p - 1; j++) {
            if (arr[i] < pivots[j]) {
                rank = j;
                break;
            }
        }
        int idx = offsets[rank]++;
        tmp[idx] = arr[i];
    }

// Step 4: Sort each block
#pragma omp parallel for
    for (int i = 0; i < p; i++) {
        std::sort(tmp + offsets[i], tmp + offsets[i] + counts[i]);
    }

// Step 5: Merge blocks
#pragma omp parallel for
    for (int i = 0; i < p; i++) {
        std::copy(tmp + offsets[i], tmp + offsets[i] + counts[i],
                  arr + i * (n / p));
    }

    // Step 6: Sort merged data
    std::sort(arr, arr + n);

    delete[] sample;
    delete[] tmp;
}

int main() {
    vector<int> data(SIZE);

    srand(SIZE);
    for (int i = 0; i < SIZE; i++) data[i] = rand() % (SIZE * 10);

    double t = omp_get_wtime();
    // add your codes begin
    sampleSort(&data[0], SIZE, 10);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE - 1; i++) assert(data[i] <= data[i + 1]);
}