- Student name: 宋家庆
- ID number: 202000130061

- Implement your Pi program "pi_rnd_N.cpp"
  - Version 0: serial program using LCG PRNG
  - Version 1: parallel program using thread-safe PRNG
  - Version 2: parallel program using leap-frog PRNG
- Compile and run your programs multiple times
- Describe your observations
当SIZE大小为100000000时
version 0
所需时间为4.167296，计算得到的pi大小为3.141593560000，误差为0.000000906410
version 1
所需时间为0.127502，计算得到的pi大小为3.141757440000，误差为0.000164786410
version 2
所需时间为0.175884，计算得到的pi大小为3.141585920000，误差为-0.000000533590
串行版本的准确度最高，thread-safe版本速度较快，但准确度较低，leap-frog可以在高效的情况下保证较高的准确度。
- Explain why this happens
thread_safe版本，每个线程都拷贝了一份初始的random_seed，但由于使用了相同的随机数种子和随机数算法，使得生成的
随机数并没有那么的随机，导致蒙特卡洛算法结果不理想。
leap-frog版本先使用了一种随机数生成算法为每个线程生成了一个随机数种子，又使用了另一种随机数生成算法在每个线程内部
使用不同的随机数种子生成随机数。较之thread-safe版本生成的随机数更加随机。能够逼近单线程生成的随机数效果。

