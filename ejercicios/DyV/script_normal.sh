#!/bin/bash

g++ -O3 src/max_vector.cpp -o bin/max
rm datos/max_datos_normal*

NUM=500

while [ $NUM -le 10000 ]; do
    	./bin/max $NUM >> datos/max_datos_normal.txt
	let NUM=$NUM+1
done


