#!/bin/bash

g++ -O3 src/insercion.cpp -o bin/insercion
rm datos/insercion_datos*

NUM=0

while [ $NUM -le 200 ]; do
    	./bin/insercion $NUM >> datos/insercion_datos.txt
	let NUM=$NUM+1
done

