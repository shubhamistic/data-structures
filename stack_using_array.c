#include <stdio.h>
#include <stdlib.h>

//function-definitions;
int mainMenu();
void push(int stack[], const int* size, int* top);
int pop(int stack[], int* size, int* top);
void display(int stack[], int top);

int main(){

    int size, top=-1;
    printf("\nEnter size of the stack: ");
    scanf("%d", &size);
    int* stack = (int*)calloc(size, sizeof(int));
    if (stack == NULL) {
        printf("\n:( Memory not allocated.\n");
        exit(0);
    }
    printf("\n:) Stack successfully Created.\n");

    int choice;
    do {
        choice = mainMenu();
        switch (choice) {
            case 1:
                push(stack, &size, &top);
                break;
            case 2:
                pop(stack, &size, &top);
                break;
            case 3:
                display(stack, top);
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

int mainMenu(){
    int choice;
    printf("\nSelect a choice\n");
    printf("1. PUSH\n");
    printf("2. POP\n");
    printf("3. DISPLAY\n");
    printf("4. EXIT\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

void push(int stack[], const int* size, int* top){
    if(*top == *size-1){
        printf("\n:( Stack Overflow.\n");
        return;
    }
    int n;
    printf("\nEnter Element to push: ");
    scanf("%d", &n);
    stack[++(*top)] = n;
    printf("\n:) PUSH SUCCESSFUL.\n");
}


int pop(int stack[], int* size, int* top){
    if(*top == -1){
        printf("\n:( Stack Underflow.\n");
        return -1;
    }
    printf("\n:) POP SUCCESSFUL.\nDATA VALUE: '%d'\n", stack[*top]);
    return stack[(*top)--];
}

void display(int stack[], int top){
    if(top == -1){
        printf("\n:( Stack is empty.\n");
        return;
    }
    printf("\n");
    for(int i=0 ; i<=top ; i++){
        printf("%d,", stack[top-i]);
    }
    printf("\n^");
    printf("\nTOP\n");
}