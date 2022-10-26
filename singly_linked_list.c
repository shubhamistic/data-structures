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
void insert(node** head);
int insertMenu();
void insertAtBeginning(node** head);
void insertAtIntermediate(node** head);
void insertAtEnd(node** head);
void delete(node** head);
int deleteMenu();
void deleteAtBeginning(node** head);
void deleteAtIntermediate(node** head);
void deleteAtEnd(node** head);
void display(node* head);

int main(){
    int choice;
    node* head = NULL;

    do {
        choice = mainMenu();
        switch (choice) {

            case 1:
                insert(&head);
                break;
            case 2:
                delete(&head);
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
    printf("Select a choice\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display\n");
    printf("4. Exit\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

int insertMenu(){
    int choice;
    printf("\nSelect Insertion option\n");
    printf("1. Insert at Beginning\n");
    printf("2. Insert at Last\n");
    printf("3. Insert at any position\n");
    printf("4. Back\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

void insert(node** head){
    int choice;
    do{
        choice = insertMenu();
        switch(choice){
            case 1:
                insertAtBeginning(head);
                break;
            case 2:
                insertAtEnd(head);
                break;
            case 3:
                insertAtIntermediate(head);
                break;
            case 4:
                break;
            default:
                printf(":( Enter valid operation number.\n");
        }
    }
    while(choice!=4);
}

void insertAtBeginning(node** head){
    node* temp = (node*)malloc(sizeof(node));

    printf("Enter data of node: ");
    scanf("%d",&temp->data);

    if(*head == NULL){
        *head = temp;
    }
    else{
        temp -> next = *head;
        *head = temp;
    }
}

void insertAtIntermediate(node** head){
    node* temp = (node*)malloc(sizeof(node));
    node* ptr = *head;

    printf("Enter data of node: ");
    scanf("%d",&temp->data);

    if(*head == NULL){
        *head = temp;
    }
    else if( (*head)->next == NULL){
        temp -> next = *head;
        *head = temp;
    }
    else{
        int n;
        printf("Enter data of the node to add new node before it: ");
        scanf("%d", &n);

        if (ptr->data == n){
            temp -> next = *head;
            *head = temp;
            printf("\n:) Element successfully added.\n");
            return;
        }
        while(ptr->next->data != n){
            if (ptr->next->next == NULL){
                printf(":( Element not found.");
                return;
            }
            ptr = ptr->next;
        }
        temp->next = ptr->next;
        ptr->next = temp;
    }
    printf("\n:) Element successfully added.\n");
}

void insertAtEnd(node** head){
    node* temp = (node*)malloc(sizeof(node));
    temp->next = NULL;
    node* ptr = *head;

    printf("Enter data of node: ");
    scanf("%d",&temp->data);

    if(*head == NULL){
        *head = temp;
        printf("\n:) Element successfully added.\n");
        return;
    }

    while(ptr->next){
        ptr = ptr->next;
    }
    ptr->next = temp;
    printf("\n:) Element successfully added.\n");
}

int deleteMenu(){
    int choice;
    printf("\nSelect Deletion option\n");
    printf("1. delete at Beginning\n");
    printf("2. delete at Last\n");
    printf("3. delete at any position\n");
    printf("4. Back\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

void delete(node** head){
    int choice;
    do{
        choice = deleteMenu();
        switch(choice){
            case 1:
                deleteAtBeginning(head);
                break;
            case 2:
                deleteAtEnd(head);
                break;
            case 3:
                deleteAtIntermediate(head);
                break;
            case 4:
                break;
            default:
                printf(":( Enter valid operation number.\n");
        }
    }
    while(choice!=4);
}

void deleteAtBeginning(node** head){
    if(*head == NULL){
        printf(":( OOPS, Nothing to delete.\n");
        return;
    }
    node* ptr = *head;
    *head = (*head)->next;
    free(ptr);
    printf("\n:) Element successfully deleted.\n");
}

void deleteAtIntermediate(node** head){
    node* ptr = *head;

    if(*head == NULL){
        printf(":( OOPS, Nothing to delete.\n");
        return;
    }
    else if( (*head)->next == NULL){
        *head = NULL;
        free(ptr);
        printf("\n:) Element successfully deleted.\n");
        return;
    }
    else{
        int n;
        printf("Enter data of the node to delete: ");
        scanf("%d", &n);

        if(ptr->data == n){
            *head = ptr->next;
            free(ptr);
            printf("\n:) Element successfully deleted.\n");
            return;
        }
        while(ptr->next->data != n){
            if(ptr->next->next == NULL){
                printf(":( Element not found.\n");
                return;
            }
            ptr = ptr->next;
        }
        node* temp = ptr->next;
        ptr->next = ptr->next->next;
        free(temp);
        printf("\n:) Element successfully deleted.\n");
    }
}

void deleteAtEnd(node** head){
    node* ptr = *head;

    if(*head == NULL){
        printf(":( OOPS, Nothing to delete.\n");
        return;
    }
    else if(ptr->next == NULL){
        free(ptr);
        *head = NULL;
        printf("\n:) Element successfully deleted.\n");
        return;
    }
    while(ptr->next->next){
        ptr = ptr->next;
    }
    free(ptr->next);
    ptr->next = NULL;
    printf("\n:) Element successfully deleted.\n");
}

void display(node* head){
    if (head == NULL){
        printf(":( OOPS, Seems like the Linked-List is empty.\n\n");
        return;
    }
    node* ptr = head;
    printf("The linked-list is:-\n");
    while(ptr){
        printf("%d,", ptr->data);
        ptr = ptr->next;
    }
    printf("\n\n");
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);
