import random as rd
in_array =[]
size = int(input("enter the size of array:"))
for _ in range(0,size):
    in_array.append(rd.randint(1, 1000))
in_array.sort()
print(in_array)

number = int(input("Enter the number to search for ::"))
def binarysearch_righmost(arr,left,right,num):
    while left<=right:
        mid = (left+right)//2
        if arr[mid]<=num:
            left = mid+1
        else:
            right = mid-1
    else:
        if left>0 and arr[left-1]==num:
            return left-1
        else:
            return -1

index = binarysearch_righmost(in_array, 0,size-1, number)
if index!=-1:
    print("Found at index",index)
else:
    print("Not found")