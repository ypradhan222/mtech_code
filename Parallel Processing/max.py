import random
array=[]
n = int(input("Enter a the size of array : "))
for _ in range(0,n):
    array.append(random.randint(1,1000))
print(array)
def find_max(array2,left, right):
   # mid = (left+right)//2
    if left == right:
        return array2[left]
    else:
        mid = (left+right)//2
        max1= find_max(array2,left,mid)
        max2 = find_max(array2,mid+1,right)
        return max(max1,max2)
maxi = find_max(array,0,n-1)
print( "Maximum : " + str(maxi))