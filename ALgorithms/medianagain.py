import random as rd
array =[]
size= int(input("Enter the size of array::"))
for _ in range(size):
   array.append(rd.randint(1, 1000))
print(array)

def grouping(array,left,right):
   group = [array[i:i+5] for i in range(left,right+1,5)]
   return group
arr = grouping(array, 0, size-1)
print(arr)