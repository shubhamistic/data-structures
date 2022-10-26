#include <stdio.h>
#include <stdlib.h>

//structure of linked-list
struct node{
    int data;
    struct node* next;
};
typedef struct node node;


int main(){

    int array[] = {1,2,3,4,5,6};
    int size = 6;

    node* temp = (node*)malloc(sizeof(node));
    temp->data = array[0];
    temp->next = NULL;

    node* head = temp;

    node* p = head;

    for(int i=1 ; i<size ; i++){
        temp = (node*)malloc(sizeof(node));
        temp->data = array[i];
        temp->next = NULL;
        p->next = temp;
        p = p->next;
    }

    //printing the linked-list
    p = head;
    while(p){
        printf("%d,", p->data);
        p = p->next;
    }
    printf("\n");

    return 0;
}




