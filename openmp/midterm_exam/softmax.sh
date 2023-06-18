size=10000000

g++ -o segment_softmax -fopenmp -DSIZE=$size segment_softmax.cpp && timeout 60s time ./segment_softmax

