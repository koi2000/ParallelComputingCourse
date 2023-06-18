size=100000000

g++ -o prime -fopenmp -DSIZE=$size prime.cpp && timeout 60s time ./prime #> testmy.log

