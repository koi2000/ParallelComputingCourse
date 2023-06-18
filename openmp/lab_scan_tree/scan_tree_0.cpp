//student name:
//id number:

#include <omp.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;


// add your codes begin
const int thrd_num = 60;
// add your codes end


int main() {
  vector<int> data(SIZE, -1);
  vector<int> pare(SIZE, -1);
  vector<int> test(SIZE, -1);

  srand(SIZE);
  { vector<int> tmp;
    for (int i = 0; i < SIZE/2; i++) {
      // 随机获取一个idx
      int idx = rand() % SIZE;
      // 找到一个data[idx]没有父亲的    
      while (data[idx] >= 0) idx = (idx + 1) % SIZE;
      if (i > 0) {
        // 把他的树高记为1
        data[idx] = 1;
        // 给他找一个父亲
        pare[idx] = tmp[rand() % tmp.size()];
        // 得到真正的树高
        test[idx] = test[pare[idx]] + data[idx];
      } else {
        // 这个节点是根节点，rank为0
        data[idx] = 0;
        test[idx] = data[idx];
      }
      // 他现在可以作为父亲了
      tmp.push_back(idx);
    }
  }

  double t = omp_get_wtime();
  // add your codes begin
  // 将data的初始值全部置为0
// #pragma omp parallel for
//     for (int i = 0; i < SIZE; i++)
//         if (data[i] == 1) data[i] = 0;

    int* cdata = new int[SIZE];
    int* cpare = new int[SIZE];
    // vector<int> cdata(SIZE, -1);
    // vector<int> cpare(SIZE, -1);
    for (int i = 0; pow(2, i) < SIZE; i++) {
        int step = pow(2, i);
        // memcpy(&cdata[0], &data[0], 4*SIZE);
        // memcpy(&cpare[0], &pare[0], 4*SIZE);
#pragma omp parallel for num_threads(thrd_num)
        for (int i = 0; i < SIZE; i++) {
            cdata[i] = data[i];
            cpare[i] = pare[i];
        }

#pragma omp parallel for num_threads(thrd_num)
        for (int j = 0; j < SIZE; j++) {
            if (pare[j] != -1) {
                data[j] = cdata[pare[j]] + step;
                pare[j] = cpare[pare[j]];
            }
        }
    }

  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, SIZE);

  for (int i = 0; i < SIZE; i++) assert(data[i] == test[i]);
}

