import sys
import os

sum=0

file = open("text.txt")
for lines in file:
	lines = lines.split(" ")
	time_string = lines[1][:-2]
	time = float(time_string)
	sum = sum + time
	#print time_string

print float(sum/10)
