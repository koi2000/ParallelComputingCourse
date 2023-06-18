#include <assert.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long
using namespace std;

// add your codes begin
#define SIZE 10000000
const ll mod = 1e8 + 10;
const ll thrd_num = 20;

typedef vector<vector<long long>> matrix;

matrix initMatrix(ll num) {
    matrix mat = vector(4, vector(4, (ll)0));
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
    matrix mat = vector(4, vector(4, (ll)0));
    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
    return mat;
}

matrix operator*(const matrix& a, const matrix& b) {
    ll n = a.size();
    ll m = b[0].size();
    ll l = b.size();
    matrix c(n, vector<ll>(m));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            for (ll k = 0; k < l; k++) {
                c[i][j] += (a[i][k] * b[k][j]) % mod;
                c[i][j] %= mod;
            }
        }
    }
    return c;
}

void rscan(vector<matrix>& data, ll size) {
    if (size == 1) return;
    vector<matrix> twoSum(size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (ll i = 0; i < twoSum.size(); i++) {
        twoSum[i] = data[2 * i + 1] * data[i * 2];
    }
    rscan(twoSum, size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (ll i = 1; i < size; i += 2) {
        data[i] = twoSum[i / 2];
        if (i + 1 < size) {
            data[i + 1] = data[i + 1]*twoSum[(i + 1) / 2 - 1];
        }
    }
}
// add your codes end

int main() {
    vector<ll> test(SIZE);
    vector<ll> data(SIZE);
    test[0] = 1;
    test[1] = 1;
    for (ll i = 2; i < SIZE; i++) {
        test[i] = (test[i - 1] + (2 * test[i - 2]) % mod) % mod;
        test[i] = (test[i] + (3 * i) % mod + 4) % mod;
    }
    double t = omp_get_wtime();
    // add your codes begin
    // vector<matrix> mats;
    // mats.push_back(initMatrix(2));

    // for (ll i = 3; i < SIZE; i++) {
    //     matrix c = initMatrix(i);
    //     mats.push_back(c * mats[i - 3]);
    // }

    vector<matrix> mats(SIZE-2);
    #pragma omp parallel for num_threads(thrd_num)
    for (ll i = 2; i < SIZE; i++) {
        mats[i-2] = initMatrix(i);
    }

    data[0] = 1;
    data[1] = 1;
    // reverse(mats.begin(), mats.end());
    rscan(mats, SIZE - 2);
    // reverse(mats.begin(),mats.end());
    #pragma omp parallel for num_threads(thrd_num)
    for (ll i = 2; i < SIZE; i++) {
        // matrix mt = initMatrix(2);
        // for (ll j = 3; j <= i; j++) {
        //     mt = mt * initMatrix(j);
        // }
        // matrix mt = initEMatrix();
        // for (ll j = i; j >= 2; j--) {
        //     mt = mt * initMatrix(j);
        // }

        // data[i] = (mt[0][0] + mt[0][1] + (3 * mt[0][2]) % mod +
        //            (4 * mt[0][3]) % mod) %
        //           mod;
        data[i] =
            (mats[i - 2][0][0] + mats[i - 2][0][1] +
             (3 * mats[i - 2][0][2]) % mod + (4 * mats[i - 2][0][3]) % mod) %
            mod;
    }
    // reverse(data.begin()+2,data.end());
    //  add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (ll i = 0; i < SIZE; i++) {
        assert (data[i] == test[i]);
    }
}
