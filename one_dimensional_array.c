#include <stdio.h>
#include <stdlib.h>

//function-definitions;
int menu();
int* create(int *size);
void insert(int* array, const int *size, int* index);
void display(int* array, const int* index);
void delete(int* array, const int *size, int *index);

int main() {

    int choice;
    int* array;
    int size = 0;
    int index = 0;

    do {
        choice = menu();
        switch (choice) {

            case 1:
                //creating an dynamic array;
                array = create(&size);
                if (array==NULL){
                    printf(":( Sorry, There was an unknown error\n");
                    printf("encountered while creating the array.\n");
                }
                else{
                    printf(":) Array of size '%d' is Successfully Created.\n\n", size);
                }
                break;
            case 2:
                if (size == 0){
                    printf(":( OOPS seems like the array was not created.\n\n");
                    break;
                }
                insert(array, &size, &index);
                break;
            case 3:
                if (size == 0){
                    printf(":( OOPS seems like the array was not created.\n\n");
                    break;
                }
                else if(index == 0){
                    printf(":( Error, No element to delete.\n\n");
                    break;
                }
                delete(array, &size, &index);
                break;
            case 4:
                if (size == 0){
                    printf(":( OOPS, Seems like the Array is not created.\n\n");
                    break;
                }
                else if(index == 0){
                    printf(":( Sorry, No element to display.\n\n");
                    break;
                }
                display(array, &index);
                break;
            case 5:
                break;
            default:
                printf(":( Enter valid operation number.\n\n");
        }
    }
    while(choice!=5);

    return 0;
}

int menu(){
    int choice;
    printf("Select a choice\n");
    printf("1. Create\n");
    printf("2. Insert\n");
    printf("3. Delete\n");
    printf("4. Display\n");
    printf("5. Exit\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

int* create(int *size){

    printf("Enter the size of the array: ");
    scanf("%d", size);

    //dynamically creating an array of size of user input;
    return (int*)malloc(sizeof(int) * (*size));
}

void insert(int* array, const int *size, int* index){

    int n;
    printf("Enter Index: ");
    scanf("%d", &n);

    if(n < 0) {
        printf(":( Error, Element index must be greater than ZERO.\n\n");
        return;
    }
    else{
        //Taking input of array element to insert from user;
        int element;
        printf("Enter Element: ");
        scanf("%d", &element);

        if(n < *index){

            //shifting the element to the right of the array;
            for (int i = *index; i > n; i--) {
                array[i] = array[i - 1];
            }
            array[n] = element;
            printf(":) Element Successfully Added.\n\n");

        }
        else{
            if(*index == *size) {
                array[*index-1] = element;
                printf(":) Element Successfully Added to index %d.\n\n", *index-1);
            }
            else{
                array[*index] = element;
                printf(":) Element Successfully Added to index %d.\n\n", *index);
            }
        }

        //increase the size of index by 1 if the index lies in range of size of array;
        if (*index < *size) {
            *index = *index + 1;
        }
    }
}

void display(int* array, const int* index){

    if (*index == 0){
        printf(":( Sorry no element in the Array.\n\n");
    }
    else{
        printf("Array is:-\n");
        for (int i = 0; i < *index; i++){
            printf("%d,", array[i]);
        }
        printf("\n\n");
    }
}

void delete(int* array, const int *size, int *index){

    int n;
    printf("Enter Index: ");
    scanf("%d", &n);

    if(n < 0) {
        printf(":( Error, Element index must be greater than ZERO.\n\n");
        return;
    }
    else if(n < *index){

        //shifting the element to the left of the array;
        for (int i = n; i < *size-1; i++) {
            array[i] = array[i + 1];
        }
        printf(":) Element Successfully Deleted.\n\n");

        //decrementing the index after deleting the element;
        *index = *index - 1;
    }
    else{
        printf(":( Sorry, Nothing was Deleted as index is out of range.\n\n");
    }
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);