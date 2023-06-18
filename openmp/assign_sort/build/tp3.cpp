#include <omp.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

void sampleSort(double *arr, int n, int p, int s) {
    // Step 1: Choose samples
    double *sample = new double[p * s];
    srand(time(NULL));
#pragma omp parallel for
    for (int i = 0; i < p * s; i++) {
        sample[i] = arr[rand() % n];
    }
    std::sort(sample, sample + p * s);

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
    int n = 100000;  // Array size
    double *arr = new double[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
    int p = 4;  // Parallelism
    double *sorted_arr = new double[n];
    double start = omp_get_wtime();
    sampleSort(arr, n, p, n / (4 * p));
    double end = omp_get_wtime();
    std::cout << "Time: " << end - start << std::endl;
    delete[] arr;
    delete[] sorted_arr;
    return 0;
}
