version=0
size=100000000

g++ -o scan_tree_$version -fopenmp -DSIZE=$size scan_tree_$version.cpp && timeout 60s time ./scan_tree_$version

