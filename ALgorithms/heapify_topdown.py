import random as rd
import math
def heapify_topdown(arr,size,index):
   root = index
   left = 2*index +1
   right = 2*index +2
   # size = len(arr)
   if left<size and arr[left]<arr[root]:
      root = left
   if right<size and arr[right]<arr[root]:
      root = right
   if root!=index:
      arr[root],arr[index] = arr[index],arr[root]
      heapify_topdown(arr,size,root) 

def min_heap(array):
   n = len(array)
   for i in range(n):
      heapify_topdown(array,n,i)
   # return array
if __name__ == "__main__":
   size = int(input("Enter the size::"))
   array = []
   for _ in range(size):
      array.append(rd.randint(1, 1000))
   print("Original Array::",array)
   min_heap(array)
   print("Min Heap::",array)