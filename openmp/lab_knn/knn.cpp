#define DIM 64
#define KNN 10
#define NBITS 6

#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

// add your codes begin
#define SIZE 20000
#define SEED 1
float dis(float *vec1, float *vec2) {
    float res = 0;
    for (int i = 0; i < DIM; i++) {
        float re = vec1[i] - vec2[i];
        res += re * re;
    }
    // return sqrt(res);  //
    return res;  //
}

bool cmp(pair<int, float> p1, pair<int, float> p2) {
    return p1.second > p2.second;
}
// add your codes end

int main() {
    srand(SIZE);
    vector<vector<float>> coord(SIZE);
    vector<vector<float>> knn(SIZE);
    for (int i = 0; i < SIZE; i++) {
        vector<float> c(DIM);
        for (int j = 0; j < DIM; j++)
            c[j] = float(rand()) / float(RAND_MAX) * 2 - 1;
        coord[i] = c;
    }

    srand(1);
    // 初始化若干个超平面
    vector<vector<float>> rnd(NBITS);
    for (int i = 0; i < NBITS; i++) {
        vector<float> r(DIM);
        for (int j = 0; j < DIM; j++)
            r[j] = float(rand()) / float(RAND_MAX) * 2 - 1;
        rnd[i] = r;
    }

    double t = omp_get_wtime();
    // add your codes begin
    // 点积计算所有点，将所有点转化为对应维度的向量
    // 将原始向量由 N * DIM 转化为 N*NBITS
    vector<string> sbit(SIZE);
    map<string, vector<int>> buckets;
#pragma omp parallel for
    for (int i = 0; i < coord.size(); i++) {
        string key = "";
        for (int k = 0; k < NBITS; k++) {
            float res = 0;
            for (int j = 0; j < DIM; j++) {
                res += (coord[i][j] * rnd[k][j]);
            }
            if (res > 0)
                key += "1";
            else
                key += "0";
        }
        sbit[i] = key;
    }

    // #pragma omp parallel for
    for (int i = 0; i < coord.size(); i++) {
        buckets[sbit[i]].push_back(i);
    }

#pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        string key = sbit[i];
        // 得到了当前节点的hash值
        // vector<int> bucket;
        vector<int> bucket = buckets[key];

        vector<pair<int, string>> stp;

        for (int tenv = 0; tenv < pow(2, NBITS); tenv++) {
            int val = 0;
            string tk = "";
            for (int b = 0; b < NBITS; b++) {
                val += (((tenv >> b) & 1) != (key[b] - '0'));
                tk += (((tenv >> b) & 1) + '0');
            }
            stp.push_back({val, tk});
        }
        sort(stp.begin(), stp.end());
        for (int j = 1; j <= 6; j++) {
            bucket.insert(bucket.end(),
                          buckets[stp[j].second].begin(),
                          buckets[stp[j].second].end());
        }

        int num = bucket.size();
        float *dist = new float[num];
        for (int k = 0; k < num; k++) {
            dist[k] = dis(&coord[i][0], &coord[bucket[k]][0]);
        }

        partial_sort(dist, dist + KNN + 1, dist + num);
        for (int j = 0; j < KNN + 1; j++) {
            knn[i].push_back(sqrt(dist[j]));
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
