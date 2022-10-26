#include <stdio.h>
#include <stdlib.h>

//function-definitions;
int menu();
int** create(int **array, int* rows, int* cols);
void addition(int** array1, int** array2, const int *row1, const int *col1, const int *row2, const int *col2);
void subtraction(int** array1, int** array2, const int *row1, const int *col1, const int *row2, const int *col2);
void multiplication(int** array1, int** array2, const int *row1, const int *col1, const int *row2, const int *col2);

int main() {

    int ar1, ac1, ar2, ac2;
    int **array1, **array2;

    printf("Create Array 1 :-\n\n");
    array1 = create(array1, &ar1, &ac1);

    printf("Create Array 2 :-\n\n");
    array2 = create(array2, &ar2, &ac2);

    int choice;
    do {
        choice = menu();
        switch (choice) {
            case 1:
                addition(array1, array2, &ar1, &ac1, &ar2, &ac2);
                break;
            case 2:
                subtraction(array1, array2, &ar1, &ac1, &ar2, &ac2);
                break;
            case 3:
                multiplication(array1, array2, &ar1, &ac1, &ar2, &ac2);
                break;
            case 4:
                break;
            default:
                printf(":( Enter valid operation number.\n\n");
        }
    }
    while(choice!=4);

    return 0;
}

int menu(){
    int choice;
    printf("\nSelect a choice\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Exit\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

int** create(int **array, int* rows, int* cols){

    int **ptr;
    printf("Enter number of rows: ");
    scanf("%d",rows);
    printf("Enter number of columns: ");
    scanf("%d",cols);

    ptr=(int**)malloc(sizeof(int)*(*rows));

    for(int i=0 ; i< *rows ; i++){

        ptr[i]=(int*)malloc(sizeof(int)*(*cols));
        for(int j=0 ; j< *cols ; j++){
            printf("Enter Array[%d][%d]: ", i, j);
            scanf("%d", &ptr[i][j]);
        }
    }

    printf("\nArray Elements are:-\n");
    for(int i=0; i< *rows ;i++){

        for(int j=0 ; j< *cols ;j++){
            printf("%d ",ptr[i][j]);
        }
        printf("\n");
    }

    return ptr;
}

void addition(int** array1, int** array2, const int *row1, const int *col1, const int *row2, const int *col2) {

    if ((*row1 == *row2) && (*col1 == *col2) && (*row1 == *col2)) {

        printf("\nArray after Addition is:-\n\n");
        for(int i=0 ; i < *row1 ; i++){
            for(int j=0 ; j < *col1 ; j++){
                printf("%d, ", array1[i][j] + array2[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("\n:( Error, Rows and columns should be same for both arrays.\n\n");
    }
}

void subtraction(int** array1, int** array2, const int *row1, const int *col1, const int *row2, const int *col2) {

    if ((*row1 == *row2) && (*col1 == *col2) && (*row1 == *col2)) {

        printf("\nArray after Subtraction is:-\n\n");
        for(int i=0 ; i < *row1 ; i++){
            for(int j=0 ; j < *col1 ; j++){
                printf("%d, ", array1[i][j] - array2[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("\n:( Error, Rows and columns should be same for both arrays.\n\n");
    }
}

void multiplication(int** array1, int** array2, const int *row1, const int *col1, const int *row2, const int *col2){

    if (*col1 == *row2) {

        printf("\nArray after Multiplication is:-\n\n");
        for(int i=0; i < *row1 ; i++){
            for (int j=0; j < *col2 ; j++){
                int sum = 0;
                for(int k=0 ; k < *row2 ; k++){
                    sum = sum + (array1[i][k] * array2[k][j]);
                }
                printf("%d, ", sum);
            }
            printf("\n");
        }
    }
    else{
        printf("\n:( Error, column of 1st array should be equal to row of 2nd array.\n\n");
    }
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);