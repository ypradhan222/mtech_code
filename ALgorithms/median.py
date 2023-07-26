import numpy as np
size = int(input("enter the size::"))
arr = np.random.randint(1,100,size=size)
np.set_printoptions(threshold=size)
print("Original array:: ",arr)

def partition(array,left,right):
   group = [ array[i:i+5] for i in range(left,right+1,5)]
   while left<=right:
      mid = (left+right)//2