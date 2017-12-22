import random
import sys
import os
import subprocess

stack_size = input("Stack Size: ")
itterations = input("Number of Itterations: ")
average = 0

i = 0;
while (i < itterations):
	my_random = random.sample(range(1, 100000), stack_size)
	lol = ' '.join(str(x) for x in my_random)
	proc = subprocess.Popen(["./push_swap " + lol], stdout=subprocess.PIPE, shell=True)
	out = proc.stdout.readlines()
	if len(out) == 0:
		continue
	average += int(out[len(out) - 1])
	wtf = ''.join(out[:-1])
	p = subprocess.Popen(["../checker/checker " + lol], stdout=subprocess.PIPE, shell=True, stdin=subprocess.PIPE)
	p.stdin.write(wtf)
	i = i + 1
print("Average operations = ", average / itterations)