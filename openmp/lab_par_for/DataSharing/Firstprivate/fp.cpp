#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 2
static long num_steps = 100000;
double step;
const int MAX = 10;
int A[MAX];

int main() {
  int incr = 0;
  #pragma omp parallel for firstprivate(incr)
  for (int i = 0; i <= MAX; i++) {
    if ((i % 2) == 0) incr++;
    A[i] = incr;
  }
  for (int i = 0; i < MAX; i++) {
    printf("%d", A[i]);
  }

  return 0;
}