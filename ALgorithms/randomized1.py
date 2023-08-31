import random
array = []
uniqueness = set()
# size = int(input("Enter the size::"))
for _ in range(10000):
   # size = 9
   # for _ in range(size):
   #    array.append(random.randint(1,10))
   array = [1,6,8,43,54,13]
   print("Original array::",array)
   priority = []
   for i in range(len(array)):
      priority.append(random.randint(1,pow(len(array),3)))

   print(priority)  
   shuffled_array = [x for _,x in sorted(zip(priority,array))]
   print("Shuffled array:: ",shuffled_array)
   uniqueness.add(tuple(shuffled_array))

print(len(uniqueness))