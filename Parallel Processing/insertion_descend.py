import random as rd
arr = []
size = int(input("enter the size::"))
for _ in range(size):
    arr.append(rd.randint(1, 1000))
print("Unsorted array:",arr)

def swap(array,num,num2):
     array[num],array[num2] = array[num2],array[num]
    
def insertion_desc(array):
    j= 1
    while j!=size:
        temp = array[j]
        i = j-1
        while i>=0 and array[i]<temp:
           swap(array,i,i+1)
           i-=1
        j+=1

insertion_desc(arr)
print("Sorted array Descending:",arr)