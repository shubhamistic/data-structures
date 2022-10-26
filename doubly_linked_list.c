#include <stdio.h>
#include <stdlib.h>

//structure of linked-list
struct node{
    struct node* prev;
    int data;
    struct node* next;
};
typedef struct node node;

struct dllist{
    node* head;
    node* tail;
};
typedef struct dllist dllist;


//function-definitions;
int mainMenu();
void insert(dllist* list);
int insertMenu();
void insertAtBeginning(dllist* list);
void insertAtIntermediate(dllist* list);
void insertAtEnd(dllist* list);
void delete(dllist* list);
int deleteMenu();
void deleteAtBeginning(dllist* list);
void deleteAtIntermediate(dllist* list);
void deleteAtEnd(dllist* list);
void display(const dllist* list);

int main(){
    int choice;
    dllist list;
    list.head = NULL;
    list.tail = NULL;

    do {
        choice = mainMenu();
        switch (choice) {

            case 1:
                insert(&list);
                break;
            case 2:
                delete(&list);
                break;
            case 3:
                display(&list);
                break;
            case 4:
                break;
            default:
                printf("\n:( Enter valid operation number.\n\n");
        }
    }
    while(choice!=4);

    return 0;
}

int mainMenu(){
    int choice;
    printf("\nSelect a choice\n");
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

void insert(dllist* list){
    int choice;
    do{
        choice = insertMenu();
        switch(choice){
            case 1:
                insertAtBeginning(list);
                break;
            case 2:
                insertAtEnd(list);
                break;
            case 3:
                insertAtIntermediate(list);
                break;
            case 4:
                break;
            default:
                printf("\n:( Enter valid operation number.\n");
        }
    }
    while(choice!=4);
}

void insertAtBeginning(dllist* list){
    node* temp = (node*)malloc(sizeof(node));
    temp->prev = NULL;

    printf("\nEnter data of node: ");
    scanf("%d",&temp->data);

    if(list->head == NULL){
        temp->next = NULL;
        list->head = temp;
        list->tail = temp;
        printf("\n:) Element successfully added.\n");
        return;
    }
    temp->next = list->head;
    list->head->prev = temp;
    list->head = temp;
    printf("\n:) Element successfully added.\n");
}

void insertAtIntermediate(dllist* list){
    node* temp = (node*)malloc(sizeof(node));

    printf("\nEnter data of node: ");
    scanf("%d",&temp->data);

    if (list->head == NULL){
        temp->next = NULL;
        temp->prev = NULL;
        list->head = temp;
        list->tail = temp;
        printf("\n:) Element successfully added.\n");
        return;
    }
    int n;
    printf("\nEnter data of the previous node: ");
    scanf("%d",&n);

    node* ptr = list->head;
    while(ptr->data != n){
        if (ptr->next == NULL){
            printf("\n:( Element not found.\n");
            return;
        }
        ptr = ptr->next;
    }
    temp->next = ptr->next;
    temp->prev = ptr;

    if(ptr->next != NULL) {
        //if the insertion occurs at last so there will be no next node.
        ptr->next->prev = temp;
    }
    ptr->next = temp;

    if(temp->next == NULL){
        list->tail = temp;
    }

    printf("\n:) Element successfully added.\n");
}

void insertAtEnd(dllist* list){
    node* temp = (node*)malloc(sizeof(node));
    temp->next = NULL;

    printf("\nEnter data of node: ");
    scanf("%d",&temp->data);

    if(list->tail == NULL){
        list->head = temp;
        list->tail = temp;
        printf("\n:) Element successfully added.\n");
        return;
    }
    temp->prev = list->tail;
    list->tail->next = temp;
    list->tail = temp;
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

void delete(dllist* list){
    int choice;
    do{
        choice = deleteMenu();
        switch(choice){
            case 1:
                deleteAtBeginning(list);
                break;
            case 2:
                deleteAtEnd(list);
                break;
            case 3:
                deleteAtIntermediate(list);
                break;
            case 4:
                break;
            default:
                printf("\n:( Enter valid operation number.\n");
        }
    }
    while(choice!=4);
}

void deleteAtBeginning(dllist* list){
    if(list->head == NULL){
        printf("\n:( OOPS, Nothing to delete.\n");
        return;
    }
    node* ptr = list->head;
    if(ptr->next != NULL) {
        ptr->next->prev = NULL;
    }
    list->head = ptr->next;
    free(ptr);
    if(list->head == NULL){
        list->tail = NULL;
    }
    printf("\n:) Element successfully deleted.\n");
}

void deleteAtIntermediate(dllist* list){
    if(list->head == NULL){
        printf("\n:( OOPS, Nothing to delete.\n");
        return;
    }
    int n;
    printf("\nEnter data of the node to delete: ");
    scanf("%d", &n);

    node* ptr = list->head;
    while(ptr->data != n){
        if(ptr->next == NULL){
            printf("\n:( Element not found.\n");
            return;
        }
        ptr = ptr->next;
    }

    if(ptr->prev != NULL){
        ptr->prev->next = ptr->next;
    }
    else{
        list->head = ptr->next;
    }

    if(ptr->next != NULL){
        ptr->next->prev = ptr->prev;
    }
    else{
        list->tail = ptr->prev;
    }
    free(ptr);
    printf("\n:) Element successfully deleted.\n");
}

void deleteAtEnd(dllist* list){
    if(list->head == NULL){
        printf("\n:( OOPS, Nothing to delete.\n");
        return;
    }
    node* ptr = list->tail;
    if(ptr->prev != NULL) {
        ptr->prev->next = NULL;
    }
    list->tail = ptr->prev;
    free(ptr);
    if(list->tail == NULL){
        list->head = NULL;
    }
    printf("\n:) Element successfully deleted.\n");
}

void display(const dllist* list){
    if (list->head == NULL){
        printf("\n:( OOPS, Seems like the Linked-List is empty.\n");
        return;
    }
    node* ptr = list->head;
    printf("\nThe linked-list is:-\n");
    while(ptr){
        printf("%d,", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);