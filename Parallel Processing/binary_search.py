import random as rd
array = []
size = int(input("Enter the size of array::"))
for i in range(0,size):
    array.append(rd.randint(1, 100))
array.sort()
print(array)
num = int(input("Enter the element to search for :: "))
def binarysearch(arr,left,right,num):
    if left>right:
            return -1
    else:
            mid = (left+right)//2
            if num == arr[mid]:
                if mid == 0 or arr[mid-1]<num:
                    return mid
                else:
                    return binarysearch(arr, left, mid-1, num)
            elif num>arr[mid]:
                return binarysearch(arr, mid+1, right, num)
            else:
               return binarysearch(arr, left, mid-1, num)

number = binarysearch(array, 0, size-1, num)
if array[number] == num:
    print("Found")
else:
    print("Not Found")