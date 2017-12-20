import random
import sys
import os

my_random = random.sample(range(1, 1000000), 11)

lol = ' '.join(str(x) for x in my_random)
# os.environ["ARG"] = lol
print (lol)