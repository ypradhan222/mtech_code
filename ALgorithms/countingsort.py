import random as rd
def counting_sort(arr):
   size = len(array)
   output = [0]*size
   count = [0 for i in range(101)] #Creating counting array for the range
   
   for i in range(0,size):
      count[arr[i]] += 1    #counting the numbers in the array
   
   for i in range(1,100):
      count[i] = count[i]+count[i-1] #Adding the indices of previous index and current index start from 1
   
   for i in range(size-1,-1,-1):
      count[arr[i]]-=1
      output[count[arr[i]]] = arr[i]  
      
   for i in range(0,size):
      arr[i] = output[i]

if __name__ == "__main__":
   size = int(input("enter the size::"))
   array = [rd.randint(1, 100) for _ in range(size)]
   print("Original array::",array)
   counting_sort(array)
   print("Sorted array::",array)