import random
array =[]
n = int(input("Enter the size of array : "))
for i in range(0,n):
    array.append(random.randint(1, 100))
print(array)

#Brute-force approach
#Finding max and then removing the largest and again finding maximum
def find_max(arr,left,right):
    if left == right:
        return arr[left]
    else:
        mid = (left+right)//2
        max1 = find_max(arr, left, mid)
        max2 = find_max(arr, mid+1, right)
        return max(max1, max2)
first_max =  find_max(array, 0, n-1)
array.remove(first_max)
second_max = find_max(array, 0, n-2)
print("Second maximum :: " +str(second_max))