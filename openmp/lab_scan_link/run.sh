version=0
size=100000000

g++ -o scan_link_$version -fopenmp -DSIZE=$size scan_link_$version.cpp && timeout 60s time ./scan_link_$version

