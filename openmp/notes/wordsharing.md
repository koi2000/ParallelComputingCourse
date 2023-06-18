## WorkSharing
可以通过omp的API来实现多线程执行循环
### for
```c++
#pragma omp parallel 
#pragma omp for 
for(i=0;i<N;i++) { 
    a[i] = a[i] + b[i];
}
```
### schedule
scheduel中有多种调度策略

`schedule(static [,chunk])`，每次结果都固定，从0开始为每个线程分配chunk次迭代

`schedule(dynamic [,chunk])`，每个线程从队列中抓取chunk次迭代，直到所有迭代都处理完毕

`schedule(guide [,chunk])`类似于动态调度，但每次分配的循环次数不同，开始比较大，以后逐渐减小。size表示每次分配的迭代次数的最小值，由于每次分配的迭代次数会逐渐减少，较少到size时，将不再减少。如果不知道size的大小，那么默认size为1，即一直减少到1。

`schedule(runtime)`根据环境变量OMP_SCHEDULE确定上述调度策略中的某一种

`schedule(auto)`调度由运行时选择(不一定是上面的任何一个)