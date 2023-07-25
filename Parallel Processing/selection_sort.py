import random as rd
# Input array generation
size = int(input("Enter the size: "))
arr = []
for _ in range(size):
   arr.append(rd.randint(1, 1000))
print("Original array:", arr)
def selection_sort(array):
    i =0
    while i<size:
        min_index = i
        j = i+1
        while j<size:
            if array[j] <array[min_index]:
                min_index = j
            j+=1
        swap(array, i, min_index)
        i+=1
    return array
def swap(array,num,num2):
    array[num],array[num2] = array[num2],array[num]

selection_sort(arr)
print(arr)