import numpy as np
import math
size = int(input("enter the size::"))
arr = np.random.randint(1,100,size=size)
np.set_printoptions(threshold=np.inf)
print("Original array:: ",arr)

def grouping(array,left,right,k):
   group = [ array[i:i+5].tolist() for i in range(left,right+1,5)] #Grouping into 5 groups
   for i in group:
      i.sort() 
   medians =[] 
   print("Groups::",group)
   for j in group:
       medians.append(find_median(j))  #finding median of each group
   print("medians list::",medians)   
   median_of_medians = find_median_of_medians(medians)
   # for m in medians:
      # median_of_medians.append([m[len(m)//2]])
   print(median_of_medians)
   sorted_inp = np.sort(array)
   array3 = partitionUsingMedian(sorted_inp,median_of_medians)
   min_index= np.where(array3==np.min(array3))[0][0]
   array3[0],array3[min_index]= array3[min_index],array3[0]
   
   index_in = np.where(array==median_of_medians)[0][0]
   if left+k == index_in:
      return median_of_medians
   elif left+k<index_in:
      return grouping(array3, 0, index_in-1, k)
   else:
      return grouping(array3, index_in+1, right, k-(index_in-left+1))

# def median(group):
   # medians =[] 
   # for j in group:
      #  medians.append([j[len(j)//2]])  #finding median of each group
   # print("medians list::",medians)   
   # num = median(medians)
   # return medians
def find_median(list):
   list.sort()
   median = math.floor(list[len(list)//2])
   return median
def find_median_of_medians(medians):
   if len(medians)==1:
      return medians[0]

   return find_median(medians)
def partitionUsingMedian(array,median):
   i,j = 1,len(array)-1
   while i<=j:
      if array[i]<=median:
         i+=1
      elif array[j]>median:
         j-=1
      else:
         array[i],array[j] = array[j],array[i]
         i+=1
         j-=1
   array[0],array[j] = array[j],array[0]
   return array
k  = int(input("Enter the kth smallest element::"))
array2 = grouping(arr, 0, size-1,k-1)
print(array2)
