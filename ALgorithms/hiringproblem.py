def hiring(array,threshold):
   current_candidate = 0 
   # array=[]
   while i<n:
      if i<threshold:
         if array[i]>current_candidate:
            current_candidate = array[i]
      else:
         if array[i]>current_candidate:
            return array[i]
      i+=1