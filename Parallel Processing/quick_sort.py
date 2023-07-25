import numpy as np
n = int(input("Enter the size ::: "))
arr = np.random.randint(1,1000,size =n)
np.printoptions(threshold=np.inf)
print("Unsorted array::",arr)
def swap(array,num,num2):
    array[num],array[num2] = array[num2],array[num]

def quick_sort(array,left,right):
    if left < right:
        mid = partition(array,left,right)
        quick_sort(array, left, mid-1)
        quick_sort(array, mid+1, right)
def partition(array,left,right):
    pivot = array[right]
    i = left -1
    j= left
    while j<right:
        if array[j]<=pivot:
            i+=1
            swap(array,i,j)
        j+=1
    swap(array,i+1,right)
    return i+1
quick_sort(arr, 0, n-1)
print("Sorted array : ",arr)
