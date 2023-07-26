import numpy as np
import math
n = int(input("enter the size::"))
array =  np.random.randint(1,1000,size = n)
np.set_printoptions(threshold=np.inf)
np.array_str(array)
print(array)

def string_reverse(array):
   i= 0
   while i<= math.floor(n/2):
      array[i],array[n-i-1] = array[n-i-1],array[i]
      i+=1

string_reverse(array)
print(array)