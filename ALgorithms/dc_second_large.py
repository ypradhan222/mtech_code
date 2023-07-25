import random
arr = []
n = int(input("Enter the size of array: "))
for i in range(0,n):
    arr.append(random.randint(1, 100))
print(arr)
def second_max(array,left,right):
    if left==right:
        maximum1 = array[left]
        return maximum1,-1
    elif right-left ==1:
        maximum1 = max(arr[left],arr[right])
        maximum2 =  min(arr[left],arr[right])
        return maximum1,maximum2
    else:
        mid = (left+right)//2
        maxi,maxii = second_max(array, left, mid)
        max3,max4 = second_max(array, mid+1, right)
        if maxi< max3:
            temp1 = max3
            if maxi<max4:
                temp2 = max4
                return temp1,temp2
            else:
                return temp1,maxi
        else:
            if maxii<max3:
                return maxi,max3
            else:
                return maxi,maxii
new,new2 = second_max(arr, 0, n-1)
print("Second Largest :: " +str(new2))
