import random as rd
import math
def heapify_topdown(arr,index):
   # root = index
   # left = 2*index +1
   # right = 2*index +2
   # # size = len(arr)
   # if left<size and arr[left]<arr[root]:
   #    root = left
   # if right<size and arr[right]<arr[root]:
   #    root = right
   # if root!=index:
   #    arr[root],arr[index] = arr[index],arr[root]
   #    heapify_topdown(arr,size,root) 
   count = 0
   root = (index-1)//2
   while root >=0 and arr[index]<arr[root]:
      arr[index],arr[root]= arr[root],arr[index]
      count +=1
      index = root
      root = (index-1)//2
   return count

def min_heap(array):
   counter =0
   n = len(array)
   for i in range(n):
      counter+= heapify_topdown(array,i)
   # return array
   return counter,array
if __name__ == "__main__":
   size = int(input("Enter the size::"))
   array = []
   for _ in range(size):
      array.append(rd.randint(1, 1000))
   print("Original Array::",array)
   count,array2 = min_heap(array)
   print("Min Heap::",array2)
   print("Swaps Count::",count)