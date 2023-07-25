import numpy as np
size = int(input("Enter the size of array:: "))
arr = np.random.randint(1,1000,size=size)
#np.set_printoptions(threshold=np.inf)
print("Original array::",arr)
def selection_desc(array):
    i= 0
    while i<size:
        max_index= i
        j= i+1
        while j<size:
            if array[j]>array[max_index]:
                max_index = j
            j+=1
        swap(array,i,max_index)
        i+=1
def swap(array,num,num2):
    array[num],array[num2] = array[num2],array[num]
np.set_printoptions(threshold=np.inf)
selection_desc(arr)
print("Sorted descending array::",arr)
