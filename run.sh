#!bin/bash

python random_generator.py 5
g++ test.cpp -lcrypt -o test
./test

while IFS='' read -r row || [[ -n "$row" ]]; do
	echo "$row"
	./User 10.105.12.62 34567 $row 5 001 >> text.txt
done  < "$1"

python average.py
