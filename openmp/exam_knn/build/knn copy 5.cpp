// student name: 宋家庆
// id number: 202000130061
#define DIM 64
#define KNN 10

#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

// add your codes begin
#define SIZE 20000
#define _mBeginASM 	__asm__ __volatile__ (
#define _mEndASM	);

// float (*dist)[SIZE]=new float[SIZE][SIZE];
inline float dis(float *vec1, float *vec2) {
    float res = 0;
    for (int i = 0; i < DIM; i++) {
        float re = vec1[i] - vec2[i];
        res += re * re;
    }
    return sqrt(res);  //
}

float quickSelect(float *nums, int l, int r, int k) {
    if (l == r) {
        return nums[l];
    }
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (nums[j] <= nums[r]) {
            i++;
            swap(nums[i], nums[j]);
        }
    }
    i++;
    swap(nums[i], nums[r]);
    int cnt = i - l + 1;
    if (cnt == k) {
        return nums[i];
    } else if (cnt > k) {
        return quickSelect(nums, l, i - 1, k);
    } else {
        return quickSelect(nums, i + 1, r, k - cnt);
    }
}

inline vector<float> bottomK1(float *nums, int n, int k) {
    float kth = quickSelect(nums, 0, n - 1, k);
    vector<float> res;
    for (int i = 0; i < n; i++) {
        if (nums[i] <= kth) {
            res.push_back(nums[i]);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

void heapify(float *nums, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && nums[left] > nums[largest]) {
        largest = left;
    }
    if (right < n && nums[right] > nums[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(nums[i], nums[largest]);
        heapify(nums, n, largest);
    }
}

void buildMaxHeap(float *nums, int n) {
    for (int i = (n >> 1) - 1; i >= 0; i--) {
        heapify(nums, n, i);
    }
}

vector<float> *bottomK2(float *nums, int n, int k) {
    buildMaxHeap(nums, k);
    // #pragma omp parallel for
    for (int i = k; i < n; i++) {
        if (nums[i] < nums[0]) {
            swap(nums[i], nums[0]);
            heapify(nums, k, 0);
        }
    }

    // auto res = ;
    // for (int i = 0; i < k; i++) {
    //     res[]nums[i]);
    // }
    sort(nums, nums + k);
    return new vector<float>(nums, nums + k);
}
const int thrd_num = 60;
// add your codes end

int main() {
    vector<vector<float>> coord(SIZE);
    vector<vector<float>> knn(SIZE);

    srand(SIZE);
    for (int i = 0; i < SIZE; i++) {
        vector<float> c(DIM);
        for (int j = 0; j < DIM; j++)
            c[j] = float(rand()) / float(RAND_MAX) * 2 - 1;
        coord[i] = c;
    }

    double t = omp_get_wtime();
    // add your codes begin

    // float **dist = new float *[SIZE];
    //     float **dist = new float *[SIZE];
    // #pragma omp parallel for num_threads(thrd_num)
    //     for (int i = 0; i < SIZE; ++i) {
    //         dist[i] = new float[SIZE];
    //     }
    float(*dist)[SIZE] = new float[SIZE][SIZE];
//     float(*coord1)[DIM] = new float[SIZE][DIM];
// #pragma omp parallel for num_threads(thrd_num)
//     for (int i = 0; i < SIZE; i++)
//         memcpy(coord1[i],&coord[i][0],DIM*4);

#pragma omp parallel for num_threads(thrd_num) schedule(dynamic)
    for (int i = 0; i < SIZE; i++) {
        dist[i][i] = 0;
        // #pragma omp parallel for num_threads(60) schedule(dynamic)
        for (int j = 0; j < i; j++) {
            // float res = 0;
            // for (int k = 0; k < DIM; k++) {
            //     float re = coord1[i][k] - coord1[j][k];
            //     res += re * re;
            // }
            // dist[i][j] = sqrt(res);
            float res = dis(&coord[i][0], &coord[j][0]);
            dist[i][j] = res;
            // dist[j][i] = res;
        }
    }

#pragma omp parallel for num_threads(thrd_num) schedule(dynamic)
    for (int i = 0; i < SIZE; i++) {
        // #pragma omp parallel for num_threads(60) schedule(dynamic)
        for (int j = i + 1; j < SIZE; j++) {
            // float res = dis(&coord[i][0], &coord[j][0]);
            dist[i][j] = dist[j][i];
        }
    }

#pragma omp parallel for num_threads(thrd_num) schedule(dynamic)
    for (int i = 0; i < SIZE; i++) {
        // int k = KNN+1;
        // buildMaxHeap(dist[i], k);
        // // #pragma omp parallel for
        // for (int j = k; j < SIZE; j++) {
        //     if (dist[i][j] < dist[i][0]) {
        //         swap(dist[i][j], dist[i][0]);
        //         heapify(dist[i], k, 0);
        //     }
        // }
        // sort(dist[i], dist[i] + k);
        // knn[i] = vector(dist[i], dist[i] + k);

        knn[i] = *bottomK2(dist[i], SIZE, KNN + 1);
    }
    // #pragma omp parallel  // num_threads(60)  // schedule(dynamic)
    //     {
    //         int id, i, nthrds;
    //         id = omp_get_thread_num();
    //         nthrds = omp_get_num_threads();
    //         for (int i = id; i < SIZE; i += nthrds) {
    //             dist[i] = new float[SIZE];
    //         }
    // #pragma omp barrier
    // #pragma omp parallel for schedule(dynamic)
    //         for (int i = id; i < coord.size(); i += nthrds) {
    //             dist[i][i] = 0;
    //             for (int j = 0; j < i; j++) {
    //                 float res = dis(coord[i], coord[j]);
    //                 dist[i][j] = res;
    //                 dist[j][i] = res;
    //             }
    //         }
    // #pragma omp barrier
    // #pragma omp parallel for schedule(dynamic)
    //         for (int i = id; i < SIZE; i += nthrds) {
    //             knn[i] = bottomK2(dist[i], SIZE, KNN + 1);
    //         }
    //     }
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    const int size = 11;
    float chksum[size];
    for (int i = 0; i < size; i++) chksum[i] = 0.0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < knn[i].size(); j++) {
            chksum[i % size] += knn[i][j];
        }
    }
    printf("checksum");
    for (int i = 0; i < size; i++) printf(" %.8e", chksum[i]);
    printf("\n");
}
