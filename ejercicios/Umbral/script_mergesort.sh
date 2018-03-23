#!/bin/bash

g++ -O3 src/mergesort.cpp -o bin/mergesort
rm datos/merge_datos*

NUM=0

while [ $NUM -le 200 ]; do
    	./bin/mergesort $NUM >> datos/merge_datos.txt
	let NUM=$NUM+1
done
