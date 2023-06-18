size=20000

g++ -o knn_0 -fopenmp -DSIZE=$size knn.cpp && timeout 60s time ./knn_0

