import random as rd
import math

def grouping(array,left,right):
   group = [array[i:i+5] for i in range(left,right+1,5)]
   return group

def find_median(list):
   list.sort()
   median = math.floor(list[len(list)//2])
   return median

def find_median_of_medians(list):
   if len(list)==1:
      return list[0]
   return find_median(list)
def swap(array,num,num2):
   array[num],array[num2] = array[num2],array[num]

def partitionUsingMedian(array,left,right,median_index):
   i ,j = left,right
   value = array[median_index]
   swap(array,left,median_index)
   while i <= j:
      if array[i]<=value:
         i+=1
      elif array[j]>value:
         j-=1
      else:
         swap(array,i,j)
         i+=1
         j-=1
   swap(array,left,j)
   return array

# def select(array,left,right,k):
#    if left==right:
#       return array[left]
#    x = find_median_of_medians(array[left:right+1])
#    index_piv = partitionUsingMedian(array, left, right, array.index(x))
#    if k == index_piv-left+1:
#       return array[index_piv]
#    elif k < index_piv-left+1:
#       return select(array, left, index_piv-1, k)
#    else:
#       return select(array, index_piv+1, right, k-(index_piv-left+1))

if __name__ == "__main__":
   # try:
      array =[]
      size= int(input("Enter the size of array::"))
      for _ in range(size):
         array.append(rd.randint(1, 1000))
      print(array)
      if size >140:
         arr2 = grouping(array, 0, size-1)
         medians = []
         for j in arr2:
            medians.append(find_median(j))
         print(medians)
         median_of_medians = find_median_of_medians(medians)
         a = partitionUsingMedian(arr2,0,size-1,array.index(median_of_medians))
         print("Median of medians ::",median_of_medians)
         print("Groups:",arr2)
         print(a)
      # k = int(input("enter the smallest kth element::"))
      # smallest_index= select(array, 0, size-1, k)
      # print(smallest_index)
   # except (ValueError,NameError,IndexError,RecursionError):
      # print("ERROR REENTER!!!")