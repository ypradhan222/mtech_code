import numpy as np
n = int(input("Enter the size ::: "))
arr = np.random.randint(1,1000,size =n)
np.printoptions(threshold=np.inf)
print("Unsorted array::",arr)
def swap(array,num,num2):
    array[num],array[num2] = array[num2],array[num]

def quick_sort(array,left,right,count):
    if left < right:
        # count = 0
        mid,count = partition(array,left,right,count)
        print(array[left:mid],array[mid],array[mid+1:])
        array,count=quick_sort(array, left, mid-1,count)
        array,count=quick_sort(array, mid+1, right,count)
    return array,count

def partition(array,left,right,count):
    # count =0
    pivot = array[right]
    i = left -1
    j= left
    while j<right:
        if array[j]<=pivot:
            i+=1
            swap(array,i,j)
            count+=1
        j+=1
    swap(array,i+1,right)
    count+=1
    return i+1,count

count = 0
arr ,count = quick_sort(arr, 0, n-1,count)
print("Sorted array : ",arr)
print("Count::",count)
