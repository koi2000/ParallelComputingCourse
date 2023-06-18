- Student name: 宋家庆
- ID number: 202000130061

- Implement your sort algorithm
  - Version 1: radix sort program
  - Version 2: sample sort program
- Compile and run your programs multiple times
- Describe your observations
sort_radix：
多次运行该算法，设置了不同的参数尝试，以每一位bit一组从低到高排序，耗时约为50s
以每四位bit为一组从第到高排序，耗时约为15s
以每八位bit为一组从第到高排序，耗时约为8-10s
sort_sample:
可以调节的参数有采样的数量和线程数量，在尝试过程中找到了几个效率较高的参数组合
线程数为30，采样数位30*35或30*500时效率在6.4-7s之间
线程数为50，采样数为50*500时效率在4.6-5s之间

- Explain why this happens
针对sort_radix:
每一组中bit位数越多，最外面循环的次数就越少，且桶的数量会越多，可以使用使用更多的线程并行，效率越高。
针对sort_sample：
一般来说线程数量越多，并行度越高，效率会越高，到达某一临界值时，提升线程数量对效率的提升会变小甚至无提升，
要协调好线程开销与并发效率的关系。
该方法里有一个可调节的参数采样数量，该值越大，越能逼近均匀分割，但同时会提高该部分排序耗时。
可以多次尝试找到一个合适取值，运气好的话，较小的采样量也能达到不错的效果。
