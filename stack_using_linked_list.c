#include <stdio.h>
#include <stdlib.h>

//structure of linked-list
struct node{
    int data;
    struct node* next;
};
typedef struct node node;

//function-definitions;
int mainMenu();
void push(node** head);
int pop(node** head);
void display(node* head);

int main(){
    int choice;
    node* head = NULL;

    do {
        choice = mainMenu();
        switch (choice) {

            case 1:
                push(&head);
                break;
            case 2:
                pop(&head);
                break;
            case 3:
                display(head);
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

void push(node** head){
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL){
        printf("\n:( Stack Overflow error.");
    }
    printf("Enter data to the node: ");
    scanf("%d",&new_node->data);
    if(*head == NULL){
        *head = new_node;
        new_node->next = NULL;
        printf("\n:) Element pushed successfully.\n");
        return;
    }
    new_node->next = *head;
    *head = new_node;
    printf("\n:) Element pushed successfully.\n");
}

int pop(node** head){
    if (*head == NULL){
        printf("\n:( nothing to pop.\n");
        return -1;
    }
    node* ptr = *head;
    int data = (*head)->data;
    *head = (*head)->next;
    free(ptr);
    printf("\n:) Element (%d) deleted successfully.\n", data);
    return data;
}

void display(node* head){
    if(head == NULL){
        printf("\n:( Nothing to display.\n");
        return;
    }
    node* ptr = head;
    printf("\n");
    while(ptr){
        printf("%d,", ptr->data);
        ptr = ptr->next;
    }
    printf("\n^\n");
    printf("TOP\n");
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);