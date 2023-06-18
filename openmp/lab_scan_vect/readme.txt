- Student name: 宋家庆
- ID number: 202000130061

- Implement your scan algorithm
  - Version 0: serial program
  - Version 1: brute-force program
  - Version 2: recursion program
- Compile and run your programs multiple times
- Describe your observations
在SIZE大小为1000的情况下，v0版本运行时间约为0.00007，
v1版本运行时间约为0.001993，v2版本运行时间约为0.001227

在SIZE大小为100000000的情况下
v0版本运行时间为0.052
v1版本速度非常慢，远低于v2版本和v0版本，在60秒内无法得到结果。
v2版本时间约为0.6-0.7之间，略高于串行版本。

- Explain why this happens

v1版本需要先做map，在做reduce，每个reduce的时间复杂度为n，计算量为n^2级别，当线程数足够多时，对每个reduce
新开一个线程，时间为最长的一次reduce所需要的时间，同时reduce过程中也可以并行，理论来说效率应该不会比v0版本低，
但在真正实现的过程中，由于线程数并没有那么多，线程的创建与回收都会有时间开销，导致brute-force的性能不如线性计算。

v2版本的计算量为[(n+n/2)+(n/2+n/4)+...+1]，约有log(n)项，计算复杂度可近似为等比数列求和，计算复杂度小于3n(txt不方便写公式)，
每一次递归求和可以并行计算来优化，但由于递归中含有大量的函数调用，开销可能会比较大。导致并行后算法的时间略高于串行版本。
