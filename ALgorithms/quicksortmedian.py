
import random as rd
def quicksort(array,left,right,count):
   if left<right:
      pivot = pivotselect(array,left,right)
      mid,count = partition(array,left,right,count)
      print(array[left:mid],array[mid],array[mid+1:])
      array,count = quicksort(array,left,mid-1,count)
      array,count = quicksort(array,mid+1,right,count)
   return array,count

def pivotselect(array,left,right):
   if len(array)==1:
      return left
   elif len(array)==2:
      return right
   else:
      median = [array[left],array[(left+right)//2],array[right]]
      median.sort()
      return left+median.index(median[1])
       
def partition(array,left,right,count):
   pivot_index = pivotselect(array,left,right)
   array[pivot_index],array[right] = array[right],array[pivot_index]
   pivot = array[right]
   i = left -1
   j = left
   while j<right:
      if array[j]<=pivot:
         i+=1
         array[i],array[j]= array[j],array[i]
         count+=1
      j+=1
   array[i+1],array[right]= array[right],array[i+1]
   count+=1
   return i+1,count
# def partition(array,left,right,count):
   # pivot_index = pivotselect(array,left,right)
   # i = left-1
   # j= right
   # pivot = array[pivot_index]
   # while i<=j:
      # if array[i]<=pivot:
         # i+=1
         # count+=1
      # elif array[j]<pivot:
         # array[i],array[j] = array[j],array[i]
         # i+=1
         # j-=1
         # count+=1
      # else:
         # j-=1
         # count+=1
   # else:
      # array[j],array[left] = array[left],array[j]
      # count+=1
   # return j,count  

if __name__ == "__main__":
   count =0
   arr=[]
   try:
      n=int(input("Enter the size ::"))
      if n <=0:
         print("Size must be positive.")
      else:
         for _ in range(n):
            arr.append(rd.randint(1,100))
         print("Original array::",arr)
         arr,count =quicksort(arr,0,n-1,count)
         print("Sorted array::",arr)
         print("Count::",count)
   except (ValueError,NameError,RecursionError) as e:
      print("ERROR")