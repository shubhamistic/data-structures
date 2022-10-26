#include <stdio.h>
#include <stdlib.h>

//function-definitions;
int (*create(int *rows))[3];

int main(){

    printf("Column are fixed with value: 3\n");

    int rows, i, j;
    int (*array)[3] = create(&rows);

    printf("\nArray Elements are:-\n");

    for(i=0;i<rows;i++){

        for(j=0;j<3;j++){
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int (*create(int *rows))[3]{

    int (*ptr)[3];
    int i,j;
    printf("Enter number of rows: ");
    scanf("%d", rows);
    ptr= malloc(sizeof(int)*(*rows));
    printf("Enter the elements in an array\n");
    for(i=0;i< *rows;i++)
    {
        for(j=0;j<3;j++) {
            printf("Enter Array[%d][%d]: ", i, j);
            scanf("%d", &ptr[i][j]);
        }
    }
    return ptr;
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);