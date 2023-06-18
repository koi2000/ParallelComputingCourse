- Watch lectures: https://icloud.qd.sdu.edu.cn:7777/link/2D2A742C095E0CFD13FEB87F405E2FEB
- Expiration date: 2023-06-18
- Implement your "Hello, World!" program "hello.cpp" of Unit 1
代码见hello文件夹
- Compile and run program "par_for.cpp" multiple times

- Describe your observations
将SIZE设置为12，多次运行结果为
58 58 58 58 61 61 61 61 57 57 57 57 12
43 43 43 43 46 46 46 46 44 44 44 44 12
24 24 24 24 53 53 53 53 39 39 39 39 12
62 62 62 62 48 48 48 48 20 20 20 20 12
#pragma omp parallel for schedule(dynamic, k)
每次输出时都会有多组数字，组数为（SIZE/k）或（SIZE/k + 1）每组数字中有k个相同的数字，k为我们指定的第二个参数

- Explain why this happens

openmp底层会为每个线程分配k次计算，
这里选用的调度方式为dynamic，运行时为随机选择可用的线程，每次运行的结果几乎都是不一样的，
一般无法做到预测使用哪些线程。
若调度方式为static，则每次运行结果都是固定的。

