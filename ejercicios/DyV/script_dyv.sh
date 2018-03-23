#!/bin/bash

g++ -O3 src/max_vector_dyv.cpp -o bin/max_dyv
rm datos/max_datos_dyv*

NUM=0

while [ $NUM -le 10000 ]; do
    ./bin/max_dyv $NUM >> datos/max_datos_dyv.txt
	let NUM=$NUM+1
done


