import random
def hiring(array, threshold):
  current_candidate = 0
  i = 0
  while i < len(array):
    if array[i] > current_candidate:
      current_candidate = array[i]
    elif i >= threshold and i < len(array):
      return array[i]
    i += 1
  return current_candidate

def randomized(array):
   priority=[]
   for i in range(len(array)):
      priority.append(random.randint(1,len(array)**3))
      shuffled_array = [x for _,x in sorted(zip(priority,array))]
   return shuffled_array

array = [random.randint(1,10) for _ in range(100)]
random_list = randomized(array)
threshold = 20
hired_candidate = hiring(random_list,threshold)
print("The hired candidate:: ",hired_candidate)  