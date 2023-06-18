version=2
size=100000000

g++ -o pi_rnd_$version -fopenmp -DSIZE=$size pi_rnd_$version.cpp && timeout 60s time ./pi_rnd_$version