import random as rd
arr = []
size = int(input("Enter the size of the array::"))
for _ in range(size):
    arr.append(rd.randint(0, 1000))
print(arr)

# def swap(array,num,num2):   
#   array[num],array[num2] = array[num2],array[num]
#
def insertion_sort(array):
    j=1
    while j!=size:
        temp = array[j]
        i =j-1
        while i>=0 and array[i]>temp:
            array[i+1] = array[i]     #swap(array,i,i+1)
            i=i-1                      #i-+1
        array[i+1] = temp             #j+=1
        j = j+1
    return array
insertion_sort(arr)
print(arr)
