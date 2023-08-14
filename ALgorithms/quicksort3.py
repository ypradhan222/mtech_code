# Implementing quick sort algorithm with three way partitioning
import random as rd 

def quicksort(array,left,right,count):
   if left<=right:
      mid,count = partition3(array,left,right,count)
      print(array[left:mid],array[mid],array[mid+1:])
      array,count = quicksort(array,left,mid-1,count)
      array,count = quicksort(array,mid+1,right,count)
   return array,count

def partition3(array,left,right,count):
   x= array[left]
   i,j,k = left,left+1,right
   while j<=k:
      if array[j]<x:
         array[i],array[j] = array[j],array[i]
         i+=1
         j+=1
         count+=1
      elif array[j]>x: 
         array[j],array[k]= array[k],array[j]
         k-=1
         count+=1
      else:
         array[j]==x
         j+=1
         count+=1
   # array[left],array[j] = array[j],array[left]
   return i,count

if __name__ == "__main__":
   array = []
   count=0
   try:
      n = int(input("Enter the size :: "))
      if n<=0:
         print("Size should be greater than 0")
      else:
         for _ in range(n):
            array.append(rd.randint(1,1000))
         print("original array ::", array)
         array,count = quicksort(array,0,len(array)-1,count)
         print("sorted 3way::",array)
         print("count::",count)
   except (ValueError,TypeError,NameError) as e:
      print("error")