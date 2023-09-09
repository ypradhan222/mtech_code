def kmp_matching(string, pattern):
    i, j = 0, 0
    found = False
    n = len(string)
    m = len(pattern)
    Next = build_next(pattern)
    
    while not found and n - i >= m - j :
        if string[i] == pattern[j]:
            i += 1
            j += 1
        elif string[i]!=pattern[j]:
            if j != 0:
               j = Next[j - 1]
            else:
               i+=1
        if j == m:
            found = True
            print("Pattern found at index:", i - j)
            # break
    if not found:
        print("Pattern not found in the string.")
        return

def build_next(pattern):
    m= len(pattern)
    array=[0]*m 
    j = 0

    for i in range(1, m):
        while j > 0 and pattern[i] != pattern[j]:
            j = array[j - 1]
        
        if pattern[i] == pattern[j]:
            j += 1
        array[i] = j
    return array

if __name__ == "__main__":
   #  inp_string = input("Enter a string: ")
   #  print("Input string:", inp_string)
   #  pattern = input("Enter a pattern: ")
#    inp_string = "adfdfdadbabafdbaabaafdadbadfdeadfdfdadfdfdljfdlfdlsfdlfd"
#    pattern = "baba"
   file1 = open('/home/dmacs-5/Documents/mtech_2023/ALgorithms/sapiens.txt','r')
   file2 = open('/home/dmacs-5/Documents/mtech_2023/ALgorithms/pattern.txt','r')
   inp_string = file1.read()
   pattern = file2.read()

   kmp_matching(inp_string, pattern)

     