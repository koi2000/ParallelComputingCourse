- Student name: 宋家庆
- ID number: 202000130061

- Watch lectures: https://icloud.qd.sdu.edu.cn:7777/link/2D2A742C095E0CFD13FEB87F405E2FEB
- Expiration date: 2023-06-18
- Implement your Pi program "pi_integral_N.cpp" of Unit 2
  - Version 0: serial program
  - Version 1: parallel program using parallel-for and reduction
  - Version 2: parallel program without using parallel-for 

代码见目录
- Compile and run your programs multiple times
三个代码统一设置线程数量为4，步数为10000000，v2版本中尝试使用了atomic和ctrtical
v0运行三次结果分别为
time 0.027952 4
pi 3.141592653590 -0.000000000000

time 0.028419 4
pi 3.141592653590 -0.000000000000

time 0.027284 4
pi 3.141592653590 -0.000000000000

v1运行三次结果分别为
time 0.009849 4
pi 3.141592653590 -0.000000000000

time 0.023802 4
pi 3.141592653590 -0.000000000000

time 0.012471 4
pi 3.141592653590 -0.000000000000

v2运行三次结果分别为
critical版本
time 0.011807 4
pi 3.141592653590 -0.000000000000

time 0.013312 4
pi 3.141592653590 -0.000000000000

time 0.010704 4
pi 3.141592653590 -0.000000000000

atomic版本
time 0.010627 4
pi 3.141592653590 -0.000000000000

time 0.010760 4
pi 3.141592653590 -0.000000000000

time 0.011253 4
pi 3.141592653590 -0.000000000000

- Describe your observations
串行版本的耗时最长，使用reduction和v2版本效率差距不大。
在步数固定的情况下，当线程数量增加时，v1和v2版本的性能会先增加，
但线程数量翻倍运行效率并不会达到对应的倍数。当线程数量到达一定值时，效率不再增加。
之后再增加线程数量，效率反而会下降。

在实现v2版本时，初始时对于for循环中每一次都进行了加锁操作，这时效率极差，
将部分变量改为线程私有，每个线程独自计算自己需要计算的部分，最后将结果原子求和，效率得到了极大提升。


- Explain why this happens
初期随着线程数量的增加，运行效率会随之增加，这是因为多个线程每个线程只执行循环的一部分，并行执行，
效率增加。
效率并不会随着线程数量翻倍，这是因为线程的创建和销毁都会占用时间
当线程数量过大时，效率下降：这说明此时该程序的执行时间用在线程创建销毁的时间已经超过的具体计算的时间，
成为了该程序的计算瓶颈。这提醒我们线程并不是越多越好。

