#include <stdio.h>
#include <stdlib.h>

//structure of a stack.
struct Stack{
    int* array;
    int size;
    int top;
};
typedef struct Stack Stack;

//function-definitions;
int mainMenu();
void push(Stack* s);
int pop(Stack* s);
void display(const Stack* s);

int main(){
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    printf("\nEnter size of the stack: ");
    scanf("%d", &(s->size));
    s->array = (int*)calloc(s->size, sizeof(int));
    if (s->array == NULL) {
        printf("\n:( Memory not allocated.\n");
        exit(0);
    }
    printf("\n:) Stack of size '%d' is successfully Created.\n", s->size);

    int choice;
    do {
        choice = mainMenu();
        switch (choice) {
            case 1:
                push(s);
                break;
            case 2:
                pop(s);
                break;
            case 3:
                display(s);
                break;
            case 4:
                free(s->array);
                free(s);
                break;
            default:
                printf("\n:( Enter valid operation number.\n");
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

void push(Stack* s){
    if(s->top == s->size-1){
        printf("\n:( Stack Overflow.\n");
        return;
    }
    int n;
    printf("\nEnter Element to push: ");
    scanf("%d", &n);
    s->array[++(s->top)] = n;
    printf("\n:) PUSH SUCCESSFUL.\n");
}

int pop(Stack* s){
    if(s->top == -1){
        printf("\n:( Stack Underflow.\n");
        return -1;
    }
    printf("\n:) POP SUCCESSFUL.\nDATA VALUE: '%d'\n", s->array[s->top]);
    return s->array[(s->top)--];
}

void display(const Stack* s){
    if(s->top == -1){
        printf("\n:( Stack is empty.\n");
        return;
    }
    printf("\n");
    for(int i=0 ; i<=s->top ; i++){
        printf("%d,", s->array[s->top-i]);
    }
    printf("\n^");
    printf("\nTOP\n");
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);