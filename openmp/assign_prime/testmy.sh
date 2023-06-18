#!/bin/bash

if [ -f testmy.log ] ; then
    cat testmy.log | grep time
    exit
fi

for i in 0 1 2 3 4 ; do
    ./prime
done | tee testmy.log | grep time

