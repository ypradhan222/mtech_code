import random
array =[]
try:
    n = int(input("Enter the size of array : "))
    for i in range(0,n):
        array.append(random.randint(1, 1000))
    print(array)
except (ValueError,NameError,TypeError) as e:
    print("ERROR!! Size can only be  integer number")

def max_min(array2,start,end):
    try:
        maximum =0
        minimum = 0
        if start == end:
            maximum= array2[start]
            minimum = array2[end]
        elif start+1 == end :
            if array2[start]<array2[end]:
                maximum  = array2[end]
                minimum = array2[start]
                return minimum,maximum
            else:
                maximum = array2[start]
                minimum = array2[end]
                return minimum,maximum
        else:
            mid = (end+start)//2
            left_min,left_max = max_min(array2, start, mid)
            right_min,right_max =  max_min(array2, mid+1, end)
            if left_min <= right_min:
               # if left_min < right_max_min:
                    minimum = left_min
            else :
                minimum = right_min

            if left_max>=right_max:
                maximum = left_max
            else: 
                maximum = right_max 
            #num1,num2 = left_max_min
            #if left_max_min[0] < right_max_min[0]:
             #   maximum = right_max_min[0]
            #else:
            #    maximum = left_max_min[0]
           #if left_max_min[1] < right_max_min[1]:
            #    minimum = left_max_min[1]
           # else:
            #    minimum = right_max_min[1]
        #maxmin =[minimum,maximum]
        return minimum,maximum
    except (ValueError,NameError,TypeError) :
        print("ERROR!! INVALID NUMBERS")
try:
    mini,maxi = max_min(array, 0, n-1)
    print("Mininum :: " +str(mini))
    print("Maximum :: " +str(maxi))
except(NameError,TypeError,ValueError,RecursionError) as e:
    print("ERROR VALUES")