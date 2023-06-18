#define INF 1e7

#include <assert.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
using namespace std;
#define SIZE 6000
inline int index(const int i, const int j) { return i * SIZE + j; }

// add your codes begin
#define max_dist -30000000
#define batch_size 9
#define alt_batch_size 9
#define type short

#pragma acc routine seq
float slice_graph(int n, float *g, int i, int j) {
    return (i < n && j < n) ? g[i * n + j] : max_dist;
}

#pragma acc routine
void fill_graph(int n, float *g, int i, int j, float ele) {
    if (i < n && j < n)
        g[i * n + j] = ele;
}

void apsp(int n, float *g) {
    const int r_cnt = (n + 32 - 1) / 32;
    const int b_cnt = (n - 1) / (batch_size * 32) + 1;
    const int a_cnt = (n - 1) / (alt_batch_size * 32) + 1;

    // Allocate memory on the device
    float *d_g;
#pragma acc data copy(g[0 : n * n])
    {
// Invert edge weights
// #pragma acc parallel loop present(g[0 : n * n])
//         for (int i = 0; i < n; i++) {
// #pragma acc loop vector
//             for (int j = 0; j < n; j++) {
//                 g[i * n + j] = -g[i * n + j];
//             }
//         }

        for (int r_index = 0; r_index < r_cnt; r_index++) {
// First Step
#pragma acc parallel loop present(g[0 : n * n])
            for (int i = r_index * 32; i < (r_index + 1) * 32; i++) {
#pragma acc loop vector
                for (int j = r_index * 32; j < (r_index + 1) * 32; j++) {
                    float cur = max_dist;

// Apply OpenACC parallel loop directive to parallelize the loop
#pragma acc loop seq
                    for (int k = 0; k < n; k++) {
                        if (i < n && j < n) {
                            float value = g[i * n + k] + g[k * n + j];
                            cur = fmax(cur, value);
                        }
                    }

                    g[i * n + j] = cur;
                }
            }

// Second Step
#pragma acc parallel loop present(g[0 : n * n])
            for (int o = 0; o < n; o += batch_size * 32) {
#pragma acc loop worker
                for (int p = 0; p < batch_size; p++) {
                    int y = o + p * 32;
#pragma acc loop vector
                    for (int i = r_index * 32; i < (r_index + 1) * 32; i++) {
                        float cur = max_dist;
#pragma acc loop seq
                        for (int k = 0; k < 32; k++) {
                            cur = fmax(cur, g[i * n + y + k] + g[k * n + y]);
                        }
                        g[i * n + y] = cur;
                    }
                }

#pragma acc loop worker
                for (int q = 0; q < batch_size; q++) {
                    int x = o + q * 32;
#pragma acc loop vector
                    for (int j = r_index * 32; j < (r_index + 1) * 32; j++) {
                        float cur = max_dist;
#pragma acc loop seq
                        for (int k = 0; k < 32; k++) {
                            cur = fmax(cur, g[x * n + k] + g[j * n + k]);
                        }
                        g[x * n + j] = cur;
                    }
                }
            }

// Third Step
#pragma acc parallel loop present(g[0 : n * n])
            for (int a = 0; a < a_cnt; a++) {
                for (int b = 0; b < a_cnt; b++) {
                    int x = a * alt_batch_size * 32;
                    int y = b * alt_batch_size * 32;
#pragma acc loop worker
                    for (int p = 0; p < alt_batch_size; p++) {
                        int i = x + p * 32;
#pragma acc loop vector
                        for (int q = 0; q < alt_batch_size; q++) {
                            int j = y + q * 32;
                            float cur = g[i * n + j];
#pragma acc loop seq
                            for (int k = 0; k < 32; k++) {
                                cur = fmax(cur, g[i * n + y + k] + g[x + k * n + j]);
                            }
                            g[i * n + j] = cur;
                        }
                    }
                }
            }
        }

// Invert edge weights back to original values
// #pragma acc parallel loop present(g[0 : n * n])
//         for (int i = 0; i < n; i++) {
// #pragma acc loop vector
//             for (int j = 0; j < n; j++) {
//                 g[i * n + j] = -g[i * n + j];
//             }
//         }

// Copy data from device to host
#pragma acc update self(g[0 : n * n])

// Free memory on the device
#pragma acc exit data delete (g)
    }
}

// add your codes end

int main() {
    const int size2 = SIZE * SIZE;
    float *data = new float[size2];
    for (int i = 0; i < size2; i++) data[i] = -INF;

    srand(SIZE);
    for (int i = 0; i < SIZE * 20; i++) {
        int prev = rand() % SIZE;
        int next = rand() % SIZE;
        if ((prev == next) || (data[index(prev, next)] > -INF)) {
            i--;
            continue;
        }
        data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
    }

    double t = omp_get_wtime();
    // add your codes begin

    apsp(6000, data);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < 20; i++) {
        int prev = rand() % SIZE;
        int next = rand() % SIZE;
        if (prev == next) {
            i--;
            continue;
        }
        printf("test %d %d %f\n", prev, next, data[index(prev, next)]);
    }
}
