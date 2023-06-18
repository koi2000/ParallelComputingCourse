#include <assert.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long
using namespace std;

// add your codes begin
#define SIZE 1000
const int mod = 1e8 + 10;
const int thrd_num = 20;

typedef vector<vector<int>> matrix;

matrix initMatrix(int num) {
    matrix mat = vector(4, vector(4, 0));
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = num;
    mat[0][3] = 1;
    mat[1][0] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
    return mat;
}

matrix initEMatrix() {
    matrix mat = vector(4, vector(4, 0));
    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
    return mat;
}

matrix operator*(const matrix& a, const matrix& b) {
    int n = a.size();
    int m = b[0].size();
    int l = b.size();
    matrix c(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < l; k++) {
                c[i][j] += (a[i][k] * b[k][j]) % mod;
                c[i][j] %= mod;
            }
        }
    }
    return c;
}

void rscan(vector<matrix>& data, int size) {
    if (size == 1) return;
    vector<matrix> twoSum(size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < twoSum.size(); i++) {
        twoSum[i] = data[i * 2] * data[2 * i + 1];
    }
    rscan(twoSum, size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 1; i < size; i += 2) {
        data[i] = twoSum[i / 2];
        if (i + 1 < size) {
            data[i + 1] = twoSum[(i + 1) / 2 - 1] * data[i + 1];
        }
    }
}
// add your codes end

int main() {
    vector<int> test(SIZE);
    vector<int> data(SIZE);
    test[0] = 1;
    test[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        test[i] = (test[i - 1] + (2 * test[i - 2]) % mod) % mod;
        test[i] = (test[i] + (3 * i) % mod + 4) % mod;
    }
    double t = omp_get_wtime();
    // add your codes begin
    vector<matrix> mats;
    for (int i = 2; i < SIZE; i++) {
        mats.push_back(initMatrix(i));
    }
    data[0] = 1;
    data[1] = 1;
    // reverse(mats.begin(),mats.end());
    // rscan(mats, SIZE - 2);
    // reverse(mats.begin(),mats.end());
    for (int i = 2; i < SIZE; i++) {
        // matrix mt = initMatrix(2);
        // for (int j = 3; j <= i; j++) {
        //     mt = mt * initMatrix(j);
        // }
        matrix mt = initEMatrix();
        for (int j = i; j >= 2; j--) {
            mt = mt * initMatrix(j);
        }

        data[i] = (mt[0][0] + mt[0][1] + (3 * mt[0][2]) % mod +
                   (4 * mt[0][3]) % mod) %
                  mod;
    }
    // reverse(data.begin()+2,data.end());
    //  add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++) {
        if(data[i] != test[i]){
            cout<<i<<" ";
        };
    }
}
