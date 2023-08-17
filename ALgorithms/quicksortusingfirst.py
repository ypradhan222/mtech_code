import random as rd
def quick_sort(array, left, right, count):
   if left < right:
      pivot_index, count = partition(array, left, right, count)
      array,count = quick_sort(array, left, pivot_index - 1, count)
      array,count = quick_sort(array, pivot_index + 1, right, count)
   return array,count

def partition(array, left, right, count):
    pivot = array[left]
    i = left + 1
    j = left + 1
    while j <= right:
        if array[j] <= pivot:
            array[i], array[j] = array[j], array[i]
            count+=1
            i += 1
        j += 1
    array[left], array[i - 1] = array[i - 1], array[left]
    count+=1
    return i - 1, count + (right - left)

if __name__ == "__main__":
    try:
        n = int(input("Enter the size: "))
        if n>0:
            arr = []
            count =0
            for _ in range(n):
                arr.append(rd.randint(1, 1000))
            print("Original array:", arr)
            arr,count = quick_sort(arr, 0, n - 1, count)
            print("Sorted array:", arr)
            print("Count::",count)
        else:
            print("Enter valid size")
    except (ValueError,NameError) as e:
        print("enter integer as size")