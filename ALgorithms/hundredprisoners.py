import random as rd
prisoners = rd.sample(range(100), 100)
# print(prisoners)
boxes = rd.sample(range(100),100)
# print(boxes)

i = 0  #prisoner starts
count = 0 #Number of prisoner survived
chains = []
while i<len(prisoners):
   counter = 0
   box_item = boxes[prisoners[i]] #box number which is same as prisoner's number
   chain = [prisoners[i]]  #Chain for this prisoner
   while counter<50:
      if prisoners[i] == box_item:   #prisoner's number equal to the box item
         count+=1
         break
      else:
         counter+=1
         box_item = boxes[box_item]   # Check for box with the number which the previous box gave
         chain.append(box_item) #Adding box number to the chain
   chains.append(chain)
   i+=1
if count==100:
   print("All survived")
   for prisoner, chain in zip(prisoners, chains):
      print(f"Prisoner {prisoner}: {' -> '.join(map(str, chain))}\n")
else: 
   print("You ALL are DEAD!!!")
