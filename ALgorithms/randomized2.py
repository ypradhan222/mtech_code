import random as rd
size = int(input("ENter the size :: "))
array = [ rd.randint(1,10) for _ in range(size)]
print("Original Array:: ",array)
for i in range(size):
   x = rd.randint(i,size-1)
   array[x],array[i] = array[i],array[x]

print("Shuffled array :: ",array)