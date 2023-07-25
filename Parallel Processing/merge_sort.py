import random as rd

# Input array generation
size = int(input("Enter the size: "))
arr = []
for _ in range(size):
    arr.append(rd.randint(1, 1000))
print("Original array:", arr)
def merge(array1, left, array2, right, result):
    i, j, k = 0, 0, 0
    while i < left and j < right: 
        if array1[i] < array2[j]:   
            result[k] = array1[i]
            i += 1
        else:
            result[k] = array2[j]
            j += 1
        k += 1

    # Copy any remaining elements from the left sub-array
    while i < left:
        result[k] = array1[i]
        i += 1
        k += 1

    # Copy any remaining elements from the right sub-array
    while j < right:
        result[k] = array2[j]
        j += 1
        k += 1

def merge_sort(array):
    size = len(array)
    if size > 1:
        mid = size // 2
        left_array = array[:mid]
        right_array = array[mid:]
        merge_sort(left_array)
        merge_sort(right_array)
        merge(left_array, len(left_array), right_array, len(right_array), array)


# Sort the array using Merge Sort
merge_sort(arr)
print("Sorted array:", arr)
