import numpy as np

def threeway_partition(array):
   n = len(array)
   x= array[0]
   i,j,k = 0,1,n-1
   while j<=k:
      if array[j]==x:
         j+=1
      elif array[j]<x:
         array[i],array[j] = array[j],array[i]
         j+=1
         i+=1
      else:
         array[j],array[k] = array[k],array[j]
         k-=1

size = int(input("enter the size of the array::"))
arr = np.random.randint(1,100,size=size)
np.set_printoptions(threshold=np.inf)
print(arr)
threeway_partition(arr)
print(arr)