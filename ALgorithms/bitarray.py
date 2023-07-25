import numpy as np

def main():
        size  = int(input("Enter the size of array: "))
        array = np.random.randint(0, 2, size=size)
        np.set_printoptions(threshold=np.inf)
        print(array)
        index = int(input("Enter the index number: "))
        if index < size:
         switch = {
            1: set_bit,
            2: turn_off,
            3: toggle,
            4: specific_index
            }

        print("OUT of these OPERATIONS CHOOSE YOU WANT TO PERFORM:")
        print("1. SETTING THE BIT")
        print("2. TURN OFF")
        print("3. TOGGLE")
        print("4. CHECK BIT")
        print("0 to QUIT")
        choice = int(input("Enter your choice: "))

        if choice in switch:
            switch[choice](array, index)
            print("New array:", array)
        elif choice not in switch:
            print("INVALID CHOICE ")
            exit() 
        else:
            print("Invalid index NUMBER")

def set_bit(array1, index):
    array1[index] = 1

def turn_off(array1, index):
    array1[index] = array1[index] & ~1

def toggle(array1, index):
    if array1[index] == 0:
        array1[index] = 1
    else:
        array1[index] = 0

def specific_index(array1, index):
    if array1[index] == 1:
        print("Bit at index {} is set to 1".format(index) + "-TRUE")
    else:
        print("Bit at index {} is set to 0".format(index) + "-FALSE")

if __name__ == "__main__":
    main()