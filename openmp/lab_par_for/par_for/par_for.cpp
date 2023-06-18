#include <omp.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

#define SIZE 12
using namespace std;


int main() {
  int test[SIZE];
  #pragma omp parallel for schedule(dynamic, 4)
  for (int i = 0; i < SIZE; i++) {
    test[i] = omp_get_thread_num();
  }
  for (int i = 0; i < SIZE; i++) {
    printf(" %d", test[i]);
  }
  printf(" %d\n", SIZE);
}

