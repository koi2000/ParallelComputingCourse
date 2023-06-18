- Student name: 宋家庆
- ID number: 202000130061

- Implement your fragment scan algorithm
- Compile and run your programs multiple times
- Describle how you incrementally implement and test your program
算法运行结果如下
time 0.090030 100000000
6.98user 1.91system 0:03.85elapsed 230%CPU (0avgtext+0avgdata 2344884maxresident)k
0inputs+0outputs (0major+586522minor)pagefaults 0swaps
平均执行时间在0.3-0.4之间，较之提供的标准答案效率提高了一倍。

首先直接复现一下之前在scan中实现的recurision算法，将其中的加法操作改为定义好的操作。
此时算法执行时间约为1秒，将递归操作中的引用传递改为值传递，时间降低到0.9s
考虑到std中定义很多额外的操作，可能会比较耗时，这里将所有的vector都转换为int*数组
此时时间降低到0.09。
