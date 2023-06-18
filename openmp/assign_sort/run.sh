version=radix
# size=100000000
size=100000000

g++ -o sort_$version -fopenmp -DSIZE=$size sort_$version.cpp && timeout 60s time ./sort_$version

