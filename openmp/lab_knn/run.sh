size=20000
seed=1

g++ -o knn -fopenmp -DSIZE=$size -DSEED=$seed knn.cpp && timeout 60s time ./knn

