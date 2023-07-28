import random as rd

def swap(array,num,num2):
   array[num],array[num2] = array[num2],array[num]

def heapify(array,left,right):
   i,j = left,right
   # L=[]
   while i<=j:
      if array[i]<= array[2*i+1] and array[i]<=array[2*i+2]:
         # L[i] = array[i]
         swap(array,array[i],array[j])
         i+=1
   return array

if __name__== "__main__":
   size = int(input("Enter the size:"))
   arr = []
   for _ in range(size):
      arr.append(rd.randint(1, 100))

   arr3 =heapify(arr, 0, size-1)
   print(arr3)