import numpy as np
size = int(input("Enter the size :: "))
arr = np.random.randint(1,1000,size=size)
np.set_printoptions(threshold=np.inf)
print("Unsorted :: ",arr)

def quick_sort_desc(array,left,right):
    if left<right:
        mid = partition(array,left,right)
        quick_sort_desc(array, left, mid-1)
        quick_sort_desc(array, mid+1, right)

def partition(array,left,right):
    pivot = array[right]
    i = left -1 
    j = left
    while j<right:
        if array[j]>=pivot:
            i+=1
            swap(array,i,j)
        j+=1
    swap(array,i+1,right) 
    return i+1

def swap(array,num,num2):
    array[num],array[num2]= array[num2],array[num]
quick_sort_desc(arr, 0, size-1)
print("Sorted descending array:: ",arr)