import random as rd
def heapify_bottom(array,index):
   count =0
   size = len(array)
   root = index
   left = 2*index+1
   right = 2*index+2
   if left<size and array[left]<array[root]:
      root = left
   if right <size and array[right]<array[root]:
      root = right
   if root != index:
      array[root],array[index]=array[index],array[root]
      count+=1
      heapify_bottom(array, root)
   return count
def min_heap(array):
   counter=0
   n= len(array)
   i = n//2-1
   while i>=0:
      counter+=heapify_bottom(array, i)
      i-=1
   return array,counter
if __name__ == "__main__":
   size = int(input("Enter the size::"))
   array = []
   for _ in range(size):
      array.append(rd.randint(1, 1000))
   print("Original Array::",array)
   array2,count = min_heap(array)
   print("Min Heap::",array2)
   print("Swap Count::",count)