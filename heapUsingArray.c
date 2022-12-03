#include <stdio.h>
#include <stdlib.h>

//structure of an Array.
struct Array{
    int size;
    int* array;
};
typedef struct Array Array;

//function-definitions;
int mainMenu();
void maxHeapify(Array* arr, int index);
void minHeapify(Array* arr, int index);
void buildMaxHeap(Array* arr);
void buildMinHeap(Array* arr);
int heapSortMenu();
void buildMaxHeapAndSort(Array* arr);
void buildMinHeapAndSort(Array* arr);
void heapSort(Array* arr);


int main(){
    Array* arr = (Array*)malloc(sizeof(Array));
    printf("\nWhat should be your Array size?: ");
    scanf("%d", &arr->size);
    arr->array = (int*)calloc(arr->size, sizeof(int));
    if (arr->array == NULL) {
        printf("\n:( Memory not allocated.\n");
        exit(0);
    }
    printf("\n:) Array of size '%d' is successfully created.\n", arr->size);

    printf("\n");
    for(int i=0 ; i<arr->size ; i++){
        printf("Enter arr[%d]: ", i);
        scanf("%d", &arr->array[i]);
    }
    printf("\n");

    int choice;
    do {
        choice = mainMenu();
        switch (choice) {
            case 1:
                buildMaxHeap(arr);
                break;
            case 2:
                buildMinHeap(arr);
                break;
            case 3:
                heapSort(arr);
                break;
            case 4:
                free(arr->array);
                free(arr);
                break;
            default:
                printf("\n:( Invalid operation number.\n");
        }
    }
    while(choice!=4);
    return 0;
}

int mainMenu(){
    int choice;
    printf("\nSelect a choice\n");
    printf("1. BUILD MAX-HEAP\n");
    printf("2. BUILD MIN-HEAP\n");
    printf("3. HEAP SORT\n");
    printf("4. EXIT\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

void maxHeapify(Array* arr, int index){
    int left = (2*index)+1;
    int right = ((2*index)+1)+1;
    int largest = index;
    if((left < arr->size) && (arr->array[left] > arr->array[index])){
        largest = left;
    }
    if((right < arr->size) && (arr->array[right] > arr->array[largest])){
        largest = right;
    }
    if(largest != index){
        int temp = arr->array[index];
        arr->array[index] = arr->array[largest];
        arr->array[largest] = temp;
        maxHeapify(arr, largest);
    }
}

void buildMaxHeap(Array* arr){
    for(int i=((arr->size)/2)-1 ; i>=0 ; i--){
        maxHeapify(arr, i);
    }

    printf("\nMax Heap:-\n");
    for(int i=0 ; i<arr->size ; i++){
        printf("%d, ", arr->array[i]);
    }
    printf("\n");
}

void minHeapify(Array* arr, int index){
    int left = (2*index)+1;
    int right = ((2*index)+1)+1;
    int smallest = index;
    if((left < arr->size) && (arr->array[left] < arr->array[index])){
        smallest = left;
    }
    if((right < arr->size) && (arr->array[right] < arr->array[smallest])){
        smallest = right;
    }
    if(smallest != index){
        int temp = arr->array[index];
        arr->array[index] = arr->array[smallest];
        arr->array[smallest] = temp;
        minHeapify(arr, smallest);
    }
}

void buildMinHeap(Array* arr){
    for(int i=((arr->size)/2)-1 ; i>=0 ; i--){
        minHeapify(arr, i);
    }

    printf("\nMin Heap:-\n");
    for(int i=0 ; i<arr->size ; i++){
        printf("%d, ", arr->array[i]);
    }
    printf("\n");
}

int heapSortMenu(){
    int choice;
    printf("\nSelect a choice\n");
    printf("1. SORT BY BUILDING MAX-HEAP\n");
    printf("2. SORT BY BUILDING MIN-HEAP\n");
    printf("3. EXIT\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

void buildMaxHeapAndSort(Array* arr){
    buildMaxHeap(arr);
    printf("\n:) Max Heap Built\n");

    int org_size = arr->size;
    for(int i=(arr->size)-1 ; i>=1 ; i--){
        int temp = arr->array[0];
        arr->array[0] = arr->array[i];
        arr->array[i] = temp;
        (arr->size)--;
        maxHeapify(arr, 0);
    }
    arr->size = org_size;

    printf("\n:) Array is sorted in Ascending order:-\n");
    for(int i=0 ; i<arr->size ; i++){
        printf("%d, ", arr->array[i]);
    }
    printf("\n");
}

void buildMinHeapAndSort(Array* arr){
    buildMinHeap(arr);
    printf("\n:) Min Heap Built\n");

    int org_size = arr->size;
    for(int i=(arr->size)-1 ; i>=1 ; i--){
        int temp = arr->array[0];
        arr->array[0] = arr->array[i];
        arr->array[i] = temp;
        (arr->size)--;
        minHeapify(arr, 0);
    }
    arr->size = org_size;

    printf("\n:) Array is sorted in Descending order:-\n");
    for(int i=0 ; i<arr->size ; i++){
        printf("%d, ", arr->array[i]);
    }
    printf("\n");
}

void heapSort(Array* arr){
    int choice;
    do {
        choice = heapSortMenu();
        switch (choice) {
            case 1:
                buildMaxHeapAndSort(arr);
                break;
            case 2:
                buildMinHeapAndSort(arr);
                break;
            case 3:
                break;
            default:
                printf("\n:( Invalid operation number.\n");
        }
    }
    while(choice!=3);
}

//Author - Shubham, github-url: "github.com/shubhamistic";