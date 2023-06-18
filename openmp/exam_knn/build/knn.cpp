// // student name: 宋家庆
// // id number: 202000130061
// #define DIM 64
// #define KNN 10

// #include <assert.h>
// #include <math.h>
// #include <omp.h>
// #include <stdlib.h>

// #include <algorithm>
// #include <cstring>
// #include <iostream>
// #include <set>
// #include <vector>
// using namespace std;

// // add your codes begin
// #define SIZE 20000
// inline float dis(vector<float>& vec1, vector<float>& vec2) {
//     float res = 0;
//     for (int i = 0; i < DIM; i++) {
//         res += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
//     }
//     return sqrt(res);
// }

// class top10list {
//    public:
//     set<float> arr;
//     top10list() {}
//     void insert(float num) {
//         arr.insert(num);
//         if (arr.size() > 10) {
//             arr.erase(arr.cbegin());
//         }
//     }
// };
// // add your codes end

// int main() {
//     vector<vector<float>> coord(SIZE);
//     vector<vector<float>> knn(SIZE);

//     srand(SIZE);
//     for (int i = 0; i < SIZE; i++) {
//         vector<float> c(DIM);
//         for (int j = 0; j < DIM; j++)
//             c[j] = float(rand()) / float(RAND_MAX) * 2 - 1;
//         coord[i] = c;
//     }

//     double t = omp_get_wtime();
//     // add your codes begin

//     //-------------------------第一种方法大约15s-----------------------------
//     //     vector<vector<float>> dist(SIZE);
//     // #pragma omp parallel for num_threads(50)
//     //     for (int i = 0; i < dist.size(); i++) {
//     //         dist[i].resize(SIZE);
//     //     }
//     float** dist = new float*[SIZE];
//     for (int i = 0; i < SIZE; ++i) {
//         dist[i] = new float[SIZE];
//     }

// #pragma omp parallel for num_threads(60)
//     for (int i = 0; i < coord.size(); i++) {
//         vector<float> arr(SIZE);
//         for (int j = 0; j < i; j++) {
//             float res = dis(coord[i], coord[j]);
//             dist[i][j] = res;
//             dist[j][i] = res;
//             // arr[j] = dis(coord[i], coord[j]);
//         }
//         // sort(dist[i].begin(), dist[i].end());
//         // sort(arr.begin(), arr.end());
//         // #pragma omp critical
//         //         {
//         //             // knn[i] = vector(dist[i].begin() + 1, dist[i].begin() +
//         //             KNN + 1); knn[i] = vector(arr.begin() + 1, arr.begin()
//         //             +KNN + 1);
//         //         }
//     }

// #pragma omp parallel for num_threads(60)
//     for (int i = 0; i < SIZE; i++) {
//         sort(dist[i], dist[i] + SIZE);
//         knn[i] = vector(dist[i] + 1, dist[i] + KNN + 1);
//     }
//     //-------------------------第一种方法大约15s-----------------------------

//     //-------------------------第二种方法大约15s-----------------------------
//     //     vector<set<float>> sts(SIZE);
//     // #pragma omp parallel for num_threads(50)
//     //     for (int i = 0; i < coord.size(); i++) {
//     //         // top10list tp;
//     //         for (int j = 0; j < SIZE; j++) {
//     //             // if (i == j) continue;
//     //             float res = dis(coord[i], coord[j]);
//     //             // tp.insert(res);
//     //             sts[i].insert(res);
//     //             if (sts[i].size() > 10) {
//     //                 sts[i].erase(sts[i].cbegin());
//     //             }
//     //         }
//     //     }
//     // #pragma omp parallel for num_threads(50)
//     //     for (int i = 0; i < coord.size(); i++) {
//     //         vector<float> arr(KNN);
//     //         int idx = 0;
//     //         for (int it : sts[i]) {
//     //             arr[idx] = it;
//     //             idx++;
//     //         }
//     //         knn[i] = arr;
//     //     }
//     //-------------------------第二种方法大约15s-----------------------------
//     // add your codes end
//     t = omp_get_wtime() - t;
//     printf("time %f %d\n", t, SIZE);

//     const int size = 11;
//     float chksum[size];
//     for (int i = 0; i < size; i++) chksum[i] = 0.0;
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < knn[i].size(); j++) {
//             chksum[i % size] += knn[i][j];
//         }
//     }
//     printf("checksum");
//     for (int i = 0; i < size; i++) printf(" %.8e", chksum[i]);
//     printf("\n");
// }

// // student name:
// // id number:

// // #define DIM 64
// // #define KNN 10

// // #include <assert.h>
// // #include <math.h>
// // #include <omp.h>
// // #include <stdlib.h>

// // #include <algorithm>
// // #include <iostream>
// // #include <vector>
// // using namespace std;

// // const int NUM_THREADS = 50;
// // // add your codes begin
// // vector<vector<float>> nearest(SIZE);
// // vector<vector<float>> nearest_2(SIZE);
// // float dis(vector<float> a, vector<float> b) {
// //     float ans = 0;
// //     omp_set_num_threads(NUM_THREADS);
// //     // #pragma omp parallel
// //     {
// //         int i, id, nthrds;
// //         float sum;
// //         for (i = 0, sum = 0.0; i < DIM; i++) {
// //             sum += (a[i] - b[i]) * (a[i] - b[i]);
// //         }
// //         ans += sum;
// //     }
// //     ans = sqrt(ans);
// //     return ans;
// // }
// // // add your codes end

// // int main() {
// //     vector<vector<float>> coord(SIZE);
// //     vector<vector<float>> knn(SIZE);

// //     srand(SIZE);
// //     for (int i = 0; i < SIZE; i++) {
// //         vector<float> c(DIM);
// //         for (int j = 0; j < DIM; j++)
// //             c[j] = float(rand()) / float(RAND_MAX) * 2 - 1;
// //         coord[i] = c;
// //     }
// //     omp_set_num_threads(NUM_THREADS);
// //     double t = omp_get_wtime();
// // // add your codes begin
// // #pragma omp parallel
// //     {
// //         int id = omp_get_thread_num();
// //         int nthrds = omp_get_num_threads();
// //         for (int i = id; i < SIZE; i += nthrds) {
// //             for (int k = 0; k < i; k++) nearest[i].push_back(1);
// //             for (int j = i; j < SIZE; j++) {
// //                 float a = dis(coord[i], coord[j]);
// //                 nearest[i].push_back(a);
// //             }
// //         }
// //     }

// // #pragma omp parallel
// //     {
// //         int id = omp_get_thread_num();
// //         int nthrds = omp_get_num_threads();
// //         for (int i = id; i < SIZE; i += nthrds) {
// //             for (int j = 0; j <= i; j++) {
// //                 nearest[i][j] = nearest[j][i];
// //             }
// //         }
// //     }

// // #pragma omp parallel
// //     {
// //         int id = omp_get_thread_num();
// //         int nthrds = omp_get_num_threads();
// //         for (int i = id; i < SIZE; i += nthrds) {
// //             sort(nearest[i].begin(), nearest[i].end());
// //             knn[i].assign(nearest[i].begin() + 1, nearest[i].begin() + KNN +
// //             1);
// //         }
// //     }
// //     // add your codes end
// //     t = omp_get_wtime() - t;
// //     printf("time %f %d\n", t, SIZE);

// //     const int size = 11;
// //     float chksum[size];
// //     for (int i = 0; i < size; i++) chksum[i] = 0.0;
// //     for (int i = 0; i < SIZE; i++) {
// //         for (int j = 0; j < knn[i].size(); j++) {
// //             chksum[i % size] += knn[i][j];
// //         }
// //     }
// //     printf("checksum");
// //     for (int i = 0; i < size; i++) printf(" %.8e", chksum[i]);
// //     printf("\n");
// // }
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
inline float dis(vector<float> &vec1, vector<float> &vec2) {
    float res = 0;
    for (int i = 0; i < DIM; i++) {
        float re = vec1[i] - vec2[i];
        res += re * re;
    }
    return sqrt(res);
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

vector<float> bottomK1(float *nums, int n, int k) {
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
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(nums, n, i);
    }
}

vector<float> bottomK2(float *nums, int n, int k) {
    buildMaxHeap(nums, k);
    // #pragma omp parallel for
    for (int i = k; i < n; i++) {
        if (nums[i] < nums[0]) {
            swap(nums[i], nums[0]);
            heapify(nums, k, 0);
        }
    }
    vector<float> res;
    for (int i = 0; i < k; i++) {
        res.push_back(nums[i]);
    }
    sort(res.begin(), res.end());
    return res;
}

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

    float **dist = new float *[SIZE];
    // #pragma omp parallel for num_threads(60)
    //     for (int i = 0; i < SIZE; ++i) {
    //         dist[i] = new float[SIZE];
    //     }

    // #pragma omp parallel for num_threads(60) schedule(dynamic)
    //     for (int i = 0; i < coord.size(); i++) {
    //         dist[i][i] = 0;
    //         for (int j = 0; j < i; j++) {
    //             float res = dis(coord[i], coord[j]);
    //             dist[i][j] = res;
    //             dist[j][i] = res;
    //         }
    //     }

    // #pragma omp parallel for num_threads(60) schedule(dynamic)
    //     for (int i = 0; i < SIZE; i++) {
    //         // sort(dist[i], dist[i] + SIZE);
    //         // knn[i] = vector(dist[i] + 1, dist[i] + KNN + 1);
    //         knn[i] = bottomK2(dist[i], SIZE, KNN + 1);
    //     }
    // #pragma omp parallel //num_threads(60)  // schedule(dynamic)
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

#pragma omp parallel  // num_threads(60)  // schedule(dynamic)
    {
        int id, i, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for (int i = id; i < SIZE; i += nthrds) {
            dist[i] = new float[SIZE];
        }
#pragma omp barrier
#pragma omp parallel for schedule(dynamic)
        for (int i = id; i < coord.size(); i += nthrds) {
            dist[i][i] = 0;
            for (int j = 0; j < i; j++) {
                float res = dis(coord[i], coord[j]);
                dist[i][j] = res;
                dist[j][i] = res;
            }
        }
#pragma omp barrier
#pragma omp parallel for schedule(dynamic)
        for (int i = id; i < SIZE; i += nthrds) {
            knn[i] = bottomK2(dist[i], SIZE, KNN + 1);
        }
    }
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
