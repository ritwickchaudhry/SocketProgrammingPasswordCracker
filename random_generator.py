from random import randint
import sys
import os

digits = int(sys.argv[1])

digits = digits - 1

file = open("random_numbers.txt","wb")

for i in range (0,10):
	data = str(i) + str(randint(10**(digits-1),10**(digits)-1)) + "\n"
	file.write(data)
	# print data