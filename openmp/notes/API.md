## 常用API

```c++
#pragma omp single
#pragma omp task
#pragma omp tasknowait

#pragma omp parallel for default(shared) private(c,eps)

```
#pragma omp task
定义一个显式的任务，可能会被遇到的线程马上执行，也可能被延迟给线程组内其他线程来执行。任务的执行，依赖于OpenMP的任务调度。

#pragma omp single 
single指令指定区域的代码只能由一组线程中的一个执行。在处理非线程安全的代码段（如I/O）时可能该指令非常有用

#pragma omp section
sections将一个任务分成独立的几个section，每个由不同的线程并行处理。