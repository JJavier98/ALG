#!/bin/bash

NUM=2000
NUM1=$NUM+1
NUM2=$NUM1+1
DAT=$NUM*$NUM1*$NUM2

while [ $NUM -ge 1 ]; do
    ./a.out $DAT >> max_datos_dyv.txt
	let NUM=$NUM-1
	let NUM1=$NUM+1
	let NUM2=$NUM1+1
	let DAT=$NUM*$NUM1*$NUM2
done
