// #include <assert.h>
// #include <omp.h>
// #include <stdlib.h>

// #include <algorithm>
// #include <iostream>
// #include <vector>
// using namespace std;

// // add your codes begin
// #define SIZE 10
// const int MOD = 1e9 + 10;
// const int thrd_num = 20;

// typedef vector<vector<int>> matrix;

// matrix initMatrix(int num) {
//     matrix mat = vector(4, vector(4, 0));
//     mat[0][0] = 1;
//     mat[0][1] = 2;
//     mat[0][2] = num;
//     mat[0][3] = 1;
//     mat[1][0] = 1;
//     mat[2][2] = 1;
//     mat[3][3] = 4;
//     return mat;
// }

// matrix operator*(const matrix& a, const matrix& b) {
//     int n = a.size();
//     int m = b[0].size();
//     int l = b.size();
//     matrix c(n, vector<int>(m));
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             for (int k = 0; k < l; k++) {
//                 c[i][j] += (a[i][k] * b[k][j]) % MOD;
//                 c[i][j] %= MOD;
//             }
//         }
//     }
//     return c;
// }

// matrix matrix_power(matrix a, int n) {
//     int m = a.size();
//     matrix ans = vector(m, vector(m, 0));
//     for (int i = 0; i < m; i++) {
//         ans[i][i] = 1;
//     }
//     while (n > 0) {
//         if (n & 1) {
//             ans = ans * a;
//         }
//         a = a * a;
//         n >>= 1;
//     }
//     return ans;
// }

// void rscan(vector<matrix>& data, int size) {
//     if (size == 1) return;
//     vector<matrix> twoSum(size / 2);
// #pragma omp parallel for num_threads(thrd_num)
//     for (int i = 0; i < twoSum.size(); i++) {
//         twoSum[i] = data[i * 2] * data[2 * i + 1];
//     }
//     rscan(twoSum, size / 2);
// #pragma omp parallel for num_threads(thrd_num)
//     for (int i = 1; i < size; i += 2) {
//         data[i] = twoSum[i / 2];
//         if (i + 1 < size) {
//             data[i + 1] = twoSum[(i + 1) / 2 - 1] * data[i + 1];
//         }
//     }
// }
// // add your codes end

// int main() {
//     vector<int> test(SIZE);
//     vector<int> data(SIZE);
//     test[0] = 1;
//     test[1] = 1;
//     for (int i = 2; i < SIZE; i++) {
//         test[i] = (test[i - 1] + (2 * test[i - 2]) % MOD) % MOD;
//         test[i] = ((test[i] + (3 * i) % MOD) % MOD + 4) % MOD;
//     }
//     double t = omp_get_wtime();
//     // add your codes begin
//     vector<int> arr(SIZE + 1, 0);
//     for (int i = 2; i < SIZE; i++) {
//         arr[i - 1] = arr[i - 2] + 3 * i + 4;
//     }
//     data[0] = 1;
//     data[1] = 1;
//     matrix a = {{1, 2}, {1, 0}};
//     for (int i = 2; i < SIZE; i++) {
//         matrix tp = matrix_power(a, i - 1);
//         data[i] = (tp[0][0] + tp[0][1]) % MOD;
//         for (int j = 2; j <= i; j++) {
//             data[i] = data[i] + (j - 1) * arr[i - 1];
//         }
//     }

//     // add your codes end
//     t = omp_get_wtime() - t;
//     printf("time %f %d\n", t, SIZE);

//     for (int i = 0; i < SIZE; i++) assert(data[i] == test[i]);
// }

#include <omp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>
#define N 1000
#define P 4
using namespace std;
int main() {
    vector<int> test(N);
    vector<int> data(N);
    test[0] = 1;
    test[1] = 1;
    for (int i = 2; i < N; i++) {
        test[i] = (test[i - 1] + (2 * test[i - 2])) ;
        test[i] = ((test[i] + (3 * i) )  + 4) ;
    }
    double t = omp_get_wtime();
    int x[N];
    int n[P] = {0};
    int i, j;

    // Initialize X0 and X1
    x[0] = 1;
    x[1] = 1;

#pragma omp parallel num_threads(P)
    {
        int id = omp_get_thread_num();
        int n_local = N / P;
        int start = id * n_local;
        int end = (id == P - 1) ? N : start + n_local;

        // Calculate the assigned part
        if (id == 0) {
            // Use the initial values X1 and X0
            for (j = 2; j < end; j++) {
                x[j] = x[j - 1] + 2 * x[j - 2] + 3 * j + 4;
            }
        } else {
            x[start] = x[start - 1] + 2 * x[start - 2] + 3 * start + 4;
            x[start + 1] = x[start] + 2 * x[start - 1] + 3 * (start + 1) + 4;
            for (j = start + 2; j < end; j++) {
                x[j] = x[j - 1] + 2 * x[j - 2] + 3 * j + 4;
            }
        }

        // Update n[id] to store the size of the assigned part
        n[id] = end - start;

// Wait for all threads to finish
#pragma omp barrier
        // Copy the assigned part to the main array
        for (j = 0; j < n[id]; j++) {
            x[start + j] = x[id * n_local + j];
        }
    }

    // Print the first 10 numbers of the sequence
    for (i = 0; i < N; i++) {
        printf("%d ", x[i]==test[i]);
    }
    // for (int i = 0; i < N; i++) assert(x[i] == test[i]);
}
