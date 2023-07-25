import random as rd
arr =[]
size = int(input("Enter the size::"))
for _ in range(size):
    arr.append(rd.randint(1, 1000))
print("Original array :: ",arr)

def merge(array1,left,array2,right,result):
    i,j,k = 0,0,0
    while i<left  and j<right:
        if array1[i]<array2[j]:
            result[k]= array2[j]
            j+=1
        else:
            result[k]= array1[i]
            i+=1
        k+=1
    while i<left:
        result[k]= array1[i]
        i+=1
        k+=1
    while j<right:
        result[k] = array2[j]
        j+=1
        k+=1
def merge_sort_desc(array):
    size = len(array)
    if size > 1:
        mid = size//2
        left_array = array[:mid]
        right_array = array[mid:]
        merge_sort_desc(left_array)
        merge_sort_desc(right_array)
        merge(left_array,len(left_array),right_array,len(right_array),array)

merge_sort_desc(arr)
print("sorted array :",arr)