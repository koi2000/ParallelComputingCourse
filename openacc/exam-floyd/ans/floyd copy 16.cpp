// #define INF 1e7

// #include <omp.h>
// #include <openacc.h>
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <algorithm>
// using namespace std;

// inline int index(const int i, const int j) {
//   return i * SIZE + j;
// }

// // add your codes begin
// // add your codes end

// int main() {
//   const int size2 = SIZE * SIZE;
//   float* data = new float[size2];
//   for (int i = 0; i < size2; i++) data[i] = -INF;

//   srand(SIZE);
//   for (int i = 0; i < SIZE*20; i++) {
//     int prev = rand() % SIZE;
//     int next = rand() % SIZE;
//     if ((prev == next) || (data[index(prev, next)] > -INF)) {
//       i--;
//       continue;
//     }
//     data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
//   }

//   double t = omp_get_wtime();
//   // add your codes begin
//   acc_set_device_num(7,acc_device_nvidia);
//   #pragma acc data copy(data[0:size2])
//   {
//     for(int k=0;k<SIZE;k++)
//     {
//       #pragma acc parallel loop gang
//       for(int i=0;i<SIZE;i++)
//       {
//         #pragma acc loop vector
//         for(int j=0;j<SIZE;j++)
//         {
//           if(data[i*SIZE+j]>=data[i*SIZE+k]+data[k*SIZE+j]) continue;
//           data[i*SIZE+j]=data[i*SIZE+k]+data[k*SIZE+j];
//         }
//       }
//     }
//   }
//   // add your codes end
//   t = omp_get_wtime() - t;
//   printf("time %f %d\n", t, SIZE);

//   for (int i = 0; i < 20; i++) {
//     int prev = rand() % SIZE;
//     int next = rand() % SIZE;
//     if (prev == next) {
//       i--;
//       continue;
//     }
//     printf("test %d %d %f\n", prev, next, data[index(prev, next)]);
//   }
// }

#define INF 1e7

#include <omp.h>
#include <openacc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
using namespace std;

inline int index(const int i, const int j)
{
  return i * SIZE + j;
}

// add your codes begin
// add your codes end

int main()
{
  const int size2 = SIZE * SIZE;
  float *data = new float[size2];
  for (int i = 0; i < size2; i++)
    data[i] = -INF;

  srand(SIZE);
  for (int i = 0; i < SIZE * 20; i++)
  {
    int prev = rand() % SIZE;
    int next = rand() % SIZE;
    if ((prev == next) || (data[index(prev, next)] > -INF))
    {
      i--;
      continue;
    }
    data[index(prev, next)] = log((rand() % 99 + 1.0) / 100);
  }

  double t = omp_get_wtime();
  // add your codes begin

  int process = 3;
  int blocksize = SIZE / process;
  float *dik = new float[SIZE]; // 第k列
  float *dkj = new float[SIZE]; // 第k行
  #pragma omp parallel for
  for (int i=0;i<SIZE;i++)//先放第0行和第0列进去
  {
    dik[i]=data[i*SIZE];
    dkj[i]=data[i];
  }
  omp_set_num_threads(process);
  #pragma omp parallel
  {
    int my_gpu = omp_get_thread_num();
    acc_set_device_num(my_gpu+5, acc_device_nvidia);
    int start = my_gpu * blocksize; // 规定好了线程数量，又启用了omp parallel，因此omp parallel块内的每一部分就是一个block
    int end = start + blocksize;
    #pragma acc data copyin(data[start*SIZE:blocksize*SIZE],dik[0:SIZE],dkj[0:SIZE])//不用整个copy，只需要copy部分即可
    {
      for (int k = 0; k < SIZE; k++)
      {
        #pragma acc update device(dik[0:SIZE],dkj[0:SIZE])
        #pragma acc parallel loop gang
        for (int i = start; i < end; i++) // 只更新block的部分
        {
          #pragma acc loop vector
          for (int j = 0; j < SIZE; j++)
          {
            if (data[i*SIZE+j]>=dik[i]+dkj[j])
              continue;
            data[i*SIZE+j]=dik[i]+dkj[j];
          }
        }
        //更新一下dik和dkj，因为没有把整个data放进GPU，所以需要在这进行预先更新
        if(k!=SIZE-1)
        {
          if(k+1>=start&&k+1<end)
          {
            #pragma acc parallel loop
            for(int i=0;i<SIZE;i++)
              dkj[i] = data[(k+1)*SIZE+i];
            #pragma acc update self(dkj[0:SIZE])
          }
          #pragma acc parallel loop
          for(int i=start;i<end;i++)
          {
            dik[i]=data[i*SIZE+k+1];
          }
          #pragma acc update self(dik[start:blocksize])
        }
        #pragma omp barrier//!需要在这里同步一下，不然可能随意更改了dik和dkj两个数组，即有的线程快有的慢，快的那个把慢的的k刷新到前面去了
      }
      #pragma acc update self(data[start*SIZE:blocksize*SIZE])//最后更新到主机。data一直在GPU中，中间可以不需要copyout，dik和dkj一直有在更新，所以最后再copyout就行
    }
  }

  // add your codes end
  t = omp_get_wtime() - t;
  printf("time %f %d\n", t, SIZE);

  for (int i = 0; i < 20; i++)
  {
    int prev = rand() % SIZE;
    int next = rand() % SIZE;
    if (prev == next)
    {
      i--;
      continue;
    }
    printf("test %d %d %f\n", prev, next, data[index(prev, next)]);
  }
}