
def kmp_matching(string,pattern,next_arr):
   i,j = 0,0
   found = False
   n = len(string)
   m = len(pattern)
   while not found and n-i>m-j:
      if string[i] == pattern[j]:
         i+=1
         j+=1
      elif string[i]!=pattern[j] and j!=0:
         j = next_arr[j-1]
      elif j == m:
         found = True
         print("index :: ",str(i-j))
      else:
         i+=1

def build_next(pattern):
   m = len(pattern)
   array = [0]*m
   i=1
   j =0
   while i<m:
      if pattern[i]==pattern[j]:
         j+=1
         array[i] = j
         i+=1
      elif j!=0:
         j = array[j-1]
      else:
         array[i] = 0
         i+=1
   return array

if __name__ == "__main__":
   inp_string = str(input("enter a string :: "))
   print(inp_string)
   next_arr = []
   pattern = str(input("enter pattern :: "))
   next_arr = build_next(pattern)
   kmp_matching(inp_string,pattern,next_arr)
     