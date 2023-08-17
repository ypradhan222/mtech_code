# import random
# arr = []
# try :
#     n = int(input("Enter the size of array: "))
#     for i in range(0,n):
#         arr.append(random.randint(1, 100))
#     print(arr)
# except (ValueError,NameError,RecursionError) as f:
#     print("ERROR!!Please put integer as size!!")

# # def second_max(array,left,right):
# #         if left==right:
# #             maximum1 = array[left]
# #             return maximum1,-1
# #         elif right-left ==1:
# #             maximum1 = max(arr[left],arr[right])
# #             maximum2 =  min(arr[left],arr[right])
# #             return maximum1,maximum2
# #         else:
# #             mid = (left+right)//2
# #             maxi,maxii = second_max(array, left, mid)
# #             max3,max4 = second_max(array, mid+1, right)
# #             if maxi< max3:
# #                 temp1 = max3
# #                 if maxi<max4:
# #                     temp2 = max4
# #                     return temp1,temp2
# #                 else:
# #                     return temp1,maxi
# #             else:
# #                 if maxii<max3:
# #                     return maxi,max3
# #                 else:
# #                     return maxi,maxii

# # def second_largest(array,left,right):
# #     if left==right:
# #         return array[left]
# #     elif left+1==right:
# #         # maxi = max(array[left],array[right])
# #         sec_max = min(array[left],array[right])
# #         return sec_max
# #     else:
# #         mid = (left+right)//2
# #         secmax1 = second_largest(array,left,mid)
# #         secmax2 = second_largest(array,mid+1,right)
# #         # maximum = max(max1,max2)
# #         # second_maximum = max(min(max1,secmax2),min(secmax1,max2))
# #         if secmax1>secmax2:
# #             return secmax1
# #         else:
# #             return secmax2
import random as rd
def find_second_max(arr, start, end):
    if start == end:
        return arr[start], float('-inf')
    if start + 1 == end:
        return (arr[start], arr[end]) if arr[start] > arr[end] else (arr[end], arr[start])
    mid = (start + end) // 2
    left_max, left_second_max = find_second_max(arr, start, mid)
    right_max, right_second_max = find_second_max(arr, mid + 1, end)
    second_max = max(left_second_max, right_second_max, min(left_max, right_max))
    if left_max > right_max:
        return left_max, second_max
    else:
        return right_max, second_max

if __name__ == "__main__": 
    try:
        n = int(input("Enter the size of the array: "))
        if n >0:
            arr = [rd.randint(1, 100) for _ in range(n)]  # Generate a random array
            print("Array:", arr)
            _, second_largest = find_second_max(arr, 0, n-1)
            print("Second Largest:", second_largest)
        else:
            print("Enter size as positive numbers")
    except ValueError:
        print("ERROR!! Please input an integer as the size.")

