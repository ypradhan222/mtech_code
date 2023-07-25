import numpy as np
size = int(input("Enter the size of array::"))
arr = np.array([input("Enter elements::") for _ in range(size)])
np.set_printoptions(threshold=np.inf)
result = ', '.join(arr)
print(result)

def partition(array):
    i,j= 1,len(array) -1
    x=array[0]
    while i<=j:
        if array[i]<=x:
            i+=1
        elif array[j]>x:
            j-=1
        else:
            array[i],array[j]= array[j],array[i]
            i+=1
            j-=1
    else:
        array[0],array[j]= array[j],array[0]
# x = int(input("Enter x::"))
# if str(x) in result:
#     partition(arr, x)
# else:
#     print("Number not in array"dwdwdw)
# arr = [6,9,4,5,1,7,3,10]
partition(arr)
print(arr)
