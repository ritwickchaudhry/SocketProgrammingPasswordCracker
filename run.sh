#!bin/bash

python random_generator.py 6
g++ test.cpp -lcrypt -o test
./test
echo "A"
while IFS='' read -r row || [[ -n "$row" ]]; do
	echo "$row"
	./newuser 10.105.12.25 45678 $row 6 001 >> text.txt
done  < "$1"

python average.py 
