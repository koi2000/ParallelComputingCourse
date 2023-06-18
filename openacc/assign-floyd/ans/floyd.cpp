#define INF 1e7

#include <omp.h>
#include <openacc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
using namespace std;


inline int index(const int i, const int j) {
  return i * SIZE + j;
}

// add your codes begin
// add your codes end


int main() {
  const int size2 = SIZE * SIZE;
  float* data = new float[size2];
  for (int i = 0; i < size2; i++) data[i] = -INF;

  srand(SIZE);
  for (int i = 0; i < SIZE*20; i++) {
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

