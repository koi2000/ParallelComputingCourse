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

struct Node {
    vector<float> point;
    int axis;
    Node* left;
    Node* right;
    Node(vector<float> coord, int a)
        : point(coord), axis(a), left(nullptr), right(nullptr) {}
};

float distance(vector<float> p1, vector<float> p2) {
    float sum = 0.0;
    for (int i = 0; i < p1.size(); ++i) {
        float diff = p1[i] - p2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

struct Compare {
    vector<float> p;
    Compare(vector<float> pt) : p(pt) {}
    bool operator()(vector<float>& a, vector<float>& b) {
        return distance(a, p) < distance(b, p);
    }
};

class KDTree {
   private:
    Node* root;
    Node* constructKDTree(vector<vector<float>>& points, int depth, int start,
                          int end) {
        if (start == end) {
            return nullptr;
        }
        int axis = depth % points[0].size();
        sort(points.begin() + start, points.begin() + end,
             [&](vector<float>& p1, vector<float>& p2) {
                 return p1[axis] < p2[axis];
             });
        int mid = start + (end - start) / 2;
        Node* node = new Node(points[mid], axis);
        node->left = constructKDTree(points, depth + 1, start, mid);
        node->right = constructKDTree(points, depth + 1, mid + 1, end);
        return node;
    }
    void findNearest(Node* node, vector<float> query, int k,
                     vector<vector<float>>& nearest) {
        if (!node) {
            return;
        }
        float d = distance(node->point, query);
        if (nearest.size() < k) {
            nearest.push_back(node->point);
            if (nearest.size() == k) {
                make_heap(nearest.begin(), nearest.end(), Compare(query));
            }
        } else {
            if (d < distance(nearest.front(), query)) {
                pop_heap(nearest.begin(), nearest.end(), Compare(query));
                nearest.back() = node->point;
                push_heap(nearest.begin(), nearest.end(), Compare(query));
            }
        }
        float diff = query[node->axis] - node->point[node->axis];
        if (diff < 0) {
            findNearest(node->left, query, k, nearest);
            if (nearest.size() < k ||
                diff * diff < distance(nearest.front(), query)) {
                findNearest(node->right, query, k, nearest);
            }
        } else {
            findNearest(node->right, query, k, nearest);
            if (nearest.size() < k ||
                diff * diff < distance(nearest.front(), query)) {
                findNearest(node->left, query, k, nearest);
            }
        }
    }

   public:
    KDTree(vector<vector<float>>& points) {
        root = constructKDTree(points, 0, 0, points.size());
    }
    vector<float> findNearest(vector<float> query, int k) {
        vector<vector<float>> nearest;
        findNearest(root, query, k, nearest);
        vector<float> res;
        res.push_back(0);
        for (int i = 0; i < k; i++) {
            res.push_back(distance(query, nearest[i]));
        }
        sort(res.begin(),res.end());
        return res;
    }
};

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

    float t = omp_get_wtime();
    // add your codes begin

    KDTree kd = KDTree(coord);
    #pragma omp parallel for num_threads(60)
    for (int i = 0; i < SIZE; i++) {
        knn[i] = kd.findNearest(coord[i], KNN+1);
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
