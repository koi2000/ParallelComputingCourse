version=2
size=1000000
#rm ./build/pi_integral_$version
g++ -o ./build/pi_integral_$version -fopenmp -DSIZE=$size pi_integral_$version.cpp && timeout 60s time ./build/pi_integral_$version

