
def hashvalue(string,prime):
   # n = len(string)
   m = len(string)
   i= 0 
   hash_value =0
   while i<m:
      hash_value += ord(string[i])
      i+=1
   hash_value = hash_value%prime
   return hash_value

def rabinkarpmatch(inp_string,pattern,prime):
   n = len(inp_string)
   m = len(pattern)
   value_of_pattern = hashvalue(pattern,prime)
   value_of_input = hashvalue(inp_string[:m],prime)
   i = 0 
   while i< n-m+1:
      if value_of_input== value_of_pattern:
            if inp_string[i:i+m]==pattern:
               print("Matched at index:: ",i)
      if i <n-m:
         value_of_input = (value_of_input+ord(inp_string[i+m])-ord(inp_string[i]))%prime
      i+=1

prime = 11
if __name__== "__main__":
   input_string = str(input("Enter the input string::"))
   # print(input_string)
   pattern = str(input("Enter the pattern:: "))
   rabinkarpmatch(input_string,pattern,prime)
