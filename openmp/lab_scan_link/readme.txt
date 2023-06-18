- Student name:
- ID number:

- Implement your list ranking algorithm
- Compile and run your programs multiple times
- Describle how you incrementally implement and test your program

当SIZE大小为100000000时，在无其他人占用的情况下，答案代码为7.964633，我的时间为5.512434
首先我们将所有的rank都初始化为0，在第i次循环里，所有的prev数组都向前跳一次，此时若某个点的prev数组不为-1，即没有跳到头节点，则将data值更新为前一位置data值+pow(2,i)
这是因为我们随着循环次数的增加，其每一次跳跃所跨越的距离指数递增。最多需要log(SIZE)次跳跃，即可实现求所有的rank
由于我们在循环对data和prev数组既有写又有读，所以我们要做一次读写分离来保证正确性，即对原数组做一次拷贝。
跳跃部分可以使用并行进行优化（由于读写分离，所以可以保证并行的正确性）
优化小trick：
初始时使用vector进行data和prev的备份，使用memcpy进行拷贝，此时时间为10.944141
之后将拷贝部分更换为多线程并发拷贝，时间降低至7.885708
考虑到vecttor作为一个stl容器，内部的维护也需要耗时，将vector更换为指针，此时时间为5.512434
