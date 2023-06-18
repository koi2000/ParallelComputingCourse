version=0
size=100000000

g++ -o scan_frag_$version -fopenmp -DSIZE=$size scan_frag_$version.cpp && timeout 60s time ./scan_frag_$version

