size=1000

g++ -o series_of_numbers -fopenmp -DSIZE=$size series_of_numbers.cpp && timeout 60s time ./series_of_numbers

