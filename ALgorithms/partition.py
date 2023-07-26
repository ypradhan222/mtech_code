import numpy as np
size = int(input("Enter the size of array::"))
arr = np.array([input("Enter elements::") for _ in range(size)])
np.set_printoptions(threshold=np.inf)
# result = arr.tolist()
result1 = '['+ ', '.join(arr)+']'
print(result1)

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
    return array 
# x = int(input("Enter x::"))
# if str(x) in result:
#     partition(arr, x)
# else:
#     print("Number not in array"dwdwdw)
# arr = [6,9,4,5,1,7,3,10]
# array2 = ', '.join(arr)
array2 =partition(arr)
result2 = '['+ ', '.join(array2)+']'
print(result2)
