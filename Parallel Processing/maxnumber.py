import random
n = input("Enter the value of n : ")
array =[]
for i in range(0,int(n)):
    array.append(random.randint(1, 100))
print(array)

def find_max(array2):
    if len(array2)==1:
        return array2[0]
    elif len(array2) == 2:
        if array2[0] < array2[1]:
           return array2[1]
           # print("Maximum:"+ str(array[1]))
        else:
            return array2[0]
            #print("Maximum:"+ str(array[0]))
    else:
        mid = len(array2)//2
        max1 = find_max(array2[:mid])
        max2 = find_max(array2[mid:])
        return max(max1, max2)
maxim = find_max(array)
print("Maximum is  :  " + str(maxim))