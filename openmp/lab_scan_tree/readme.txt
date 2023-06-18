- Student name:
- ID number:

- Implement your tree ranking algorithm
- Compile and run your programs multiple times
- Compare the running times of your list ranking and tree ranking algorithms
- Explain your observations
tree的scan算法逻辑和link的逻辑基本是一致的，从较远节点更新某一点的rank的迭代轮数比较近节点所需要的
迭代轮数更多，所以使用相同的逻辑可以保证正确性。
对scan_link和scan_tree进行对比，在同样使用50个线程，SIZE大小为100000000时，scan_link所需要的时间
为5.512434，而scan_tree所需要的时间为1.976432。可以发现scan_tree所需时间更少，这是因为tree在相同
节点数量的情况下，由于树可以有多个儿子节点，而link只会有一个儿子节点，数得高度较之link比较低，所需要
的迭代次数较少，所以所需时间更少。
