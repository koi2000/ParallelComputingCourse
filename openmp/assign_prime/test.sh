#!/bin/bash

if [ -f test.log ] ; then
    cat test.log | grep time
    exit
fi

for i in 0 1 2 3 4 ; do
    ./prime_solution
done | tee test.log | grep time

