#include <stdio.h>
#include <stdlib.h>

//function-definitions;
int menu();
int* create(int *size);
int linearSearch(const int array[], int size, int element);
void bubbleSort(int array[], int size);
int binarySearch(const int array[], int size, int element);


int main() {

    int choice;
    int *array;
    int size = 0;
    int element;
    int result;

    do {
        choice = menu();
        switch (choice) {

            case 1:
                array = create(&size);
                if (array==NULL){
                    printf(":( Sorry, There was an unknown error\n");
                    printf("encountered while creating the array.\n");
                }
                else{
                    printf(":) Array of size '%d' is Successfully Created.\n\n", size);
                }
                break;

            case 2: // searching using Linear Search algorithm;
                if (size == 0){
                    printf(":( OOPS seems like the array was not created.\n\n");
                    break;
                }
                printf("\n");
                printf("Enter Element to Search: ");
                scanf("%d", &element);

                result = linearSearch(array, size, element);
                if (result == -1) {
                    printf("\n:( Element NOT found.\n\n");
                } else {
                    printf("\n:) Element found at index %d.\n\n", result);
                }
                break;

            case 3: // searching using Binary Search algorithm;
                if (size == 0){
                    printf(":( OOPS seems like the array was not created.\n\n");
                    break;
                }
                //sorting the array using bubble sort method;
                printf("\nSorting the array...\n");
                bubbleSort(array, size);
                printf("Array sorted successfully.\n");

                //searching the element using binary search algorithm;
                printf("\n");
                printf("Enter Element to Search: ");
                scanf("%d", &element);

                result = binarySearch(array, size, element);
                if (result == -1) {
                    printf("\n:( Element NOT found.\n\n");
                } else {
                    printf("\n:) Element found at index %d.\n\n", result);
                }
                break;

            case 4:
                break;

            default:
                printf(":( Enter valid operation number.\n\n");
        }
    }
    while (choice != 4);

    return 0;
}

int menu(){
    int choice;
    printf("Select a choice\n");
    printf("1. Create Array\n");
    printf("2. Linear Search\n");
    printf("3. Binary Search\n");
    printf("4. Exit\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

int* create(int *size){

    printf("Enter the size of the array: ");
    scanf("%d", size);

    //dynamically creating an array of size of user input;
    int* array = (int *) malloc(sizeof(int) * (*size));

    for(int i=0 ; i< *size ; i++){
        printf("Enter Array[%d]: ", i);
        scanf("%d", &array[i]);
    }

    return array;
}

int linearSearch(const int array[], int size, int element){

    for(int i=0 ; i<size ; i++){
        if(array[i]==element){
            return i;
        }
    }
    return -1;
}

void bubbleSort(int array[], int size){

    for(int i=0 ; i<size-1 ; i++){
        for(int j=0 ; j<size-i-1 ; j++){
            if (array[j] > array[j+1]){
                int temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            }
        }
    }
}

int binarySearch(const int array[], int size, int element){

    int start = 0;
    int end = size;
    while(start <= end){

        int mid = (start + end)/2;
        if (array[mid] == element){
            return mid;
        }
        else if(element < array[mid]){
            end = mid-1;
        }
        else{
            start = mid+1;
        }
    }
    return -1;
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);