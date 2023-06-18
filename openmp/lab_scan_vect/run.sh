version=0
size=10000000

g++ -o scan_vect_$version -fopenmp -DSIZE=$size scan_vect_$version.cpp && timeout 60s time ./scan_vect_$version

