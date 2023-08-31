import random as rd
import math

def grouping(array, left, right):
    groups = [array[i:i + 5] for i in range(left, right + 1, 5)]
    return groups

def find_median(lst):
    lst.sort()
    median = math.floor(lst[len(lst) // 2])
    return median

def partitionUsingMedian(array, median_index):
    if len(array) <= 5:
        array.sort()
        return array[median_index]

    groups = grouping(array, 0, len(array) - 1)
    medians = [find_median(group) for group in groups]
    median_of_medians = partitionUsingMedian(medians, len(medians) // 2)

    array1, array2, array3 = [], [], []
    for i in array:
        if i < median_of_medians:
            array1.append(i)
        elif i > median_of_medians:
            array3.append(i)
        else:
            array2.append(i)

    if median_index < len(array1):
        return partitionUsingMedian(array1, median_index)
    elif median_index < len(array1) + len(array2):
        return median_of_medians
    else:
        return partitionUsingMedian(array3, median_index - len(array1) - len(array2))

if __name__ == "__main__":
    array = []
    try:
      size = int(input("Enter the size of array: "))
      if size >1:
        for _ in range(size):
            array.append(rd.randint(1, 1000))

        print("Input Array:", array)

        if size > 140:
            median = partitionUsingMedian(array, size // 2)
            print("Median of Medians:", median)
        else:
            array.sort()
            median = array[len(array) // 2]
            print("Median is:", median)
      else:
        print("Size should be positive")
    except (ValueError,IndexError):
      print("ERROR")