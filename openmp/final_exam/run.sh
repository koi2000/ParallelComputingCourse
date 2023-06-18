size=1000

g++ -o circle -fopenmp -DSIZE=$size circle.cpp && timeout 60s time ./circle

