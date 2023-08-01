import random as rd

def swap(array,num,num2):
   array[num],array[num2] = array[num2],array[num]

def heapify(array,n,index):
   i = 2*index+1
   j= 2*index+2
   largest = index
   if i<n and array[i]>array[largest]:
      largest = i
   if j<n and array[j] >array[largest]:
      largest = j
   if largest!=index:
      swap(array, index, largest)
      heapify(array,n, largest)

def heap_sort(array):
   size = len(array)
   i = size//2 -1
   while i>=0:
      heapify(array,size, i)
      i-=1
   i = size-1
   while i>0:
      swap(array, 0, i)
      heapify(array,i,0)
      i-=1

if __name__== "__main__":
   try:
      size = int(input("Enter the size:"))
      if size < 0:
         raise ValueError("Size cannot be negative")
      arr = []
      for _ in range(size):
         arr.append(rd.randint(1, 100))

      heap_sort(arr)
      print(arr)
   except (NameError,ValueError,IndexError) as e:
      print(e)