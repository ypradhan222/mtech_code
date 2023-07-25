#include<stdio.h>
void swap(int array[],int num,int num2){
    int temp;
    temp = array[num];
    array[num]=array[num2];
    array[num2] = temp;
}
void selection_sort(int array[],int size){
    int i =0;
    int j;
    while (i < size)
    {
        int min_index = i;
        j=i+1;
        while(j<size){
            if (array[j]<array[min_index])
            {
                min_index = j;
            }
             j++;
        }
        swap(array,i,min_index);
        i++;
    }
}

int main(){
    int size;
    printf("Enter the size::");
    scanf("%d",&size);
    int arr[size];
    printf("Enter the elements of array:");
    for(int i =0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    selection_sort(arr,size);
    for(int i = 0;i<size;i++){
        printf("%d",arr[i]);
    }
return 0;
}
