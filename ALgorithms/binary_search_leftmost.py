import random as rd
import math
size = int(input("Enter the size of array::"))
array=[]
for i in range(0,size):
    array.append(rd.randint(1, 1000))
array.sort()
print(array)
number = int(input("Enter the number to search for :: "))
def binarysearch_leftmost(arr,left,right,num):
    while left!=right:
        mid = (left+ right)//2
        if arr[mid] < num:
            left = mid+1
        else:
            right = mid
    else: #left == right
        if arr[left]==num:
            return left
        else:
            return -1

index = binarysearch_leftmost(array, 0, size-1, number)
if index!=-1:
    print("Found at index",index)
else:
    print("Not Found")