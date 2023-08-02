import random as rd
def heapify_bottom(array,index):
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
      heapify_bottom(array, root)
   
def min_heap(array):
   n= len(array)
   i = n//2-1
   while i>=0:
      heapify_bottom(array, i)
      i-=1

if __name__ == "__main__":
   size = int(input("Enter the size::"))
   array = []
   for _ in range(size):
      array.append(rd.randint(1, 1000))
   print("Original Array::",array)
   min_heap(array)
   print("Min Heap::",array)