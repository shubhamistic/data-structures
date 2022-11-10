#include <stdio.h>
#include <stdlib.h>

//structure of a Queue.
struct Queue{
    int rear;
    int front;
    int size;
    int* array;
};
typedef struct Queue Queue;

//function-definitions;
int mainMenu();
void enqueue(Queue* queue);
int dequeue(Queue* queue);
int search(const Queue* queue);
void display(const Queue* queue);

int main(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    printf("\nWhat should be your queue size?: ");
    scanf("%d", &queue->size);
    queue->array = (int*)calloc(queue->size, sizeof(int));
    if (queue->array == NULL) {
        printf("\n:( Memory not allocated.\n");
        exit(0);
    }
    queue->front = -1;
    queue->rear = -1;
    printf("\n:) Queue of size '%d' is successfully created.\n", queue->size);

    int choice;
    do {
        choice = mainMenu();
        switch (choice) {
            case 1:
                enqueue(queue);
                break;
            case 2:
                dequeue(queue);
                break;
            case 3:
                search(queue);
                break;
            case 4:
                display(queue);
                break;
            case 5:
                free(queue->array);
                free(queue);
                break;
            default:
                printf("\n:( Invalid operation number.\n");
        }
    }
    while(choice!=5);

    return 0;
}

int mainMenu(){
    int choice;
    printf("\nSelect a choice\n");
    printf("1. ENQUEUE ELEMENT\n");
    printf("2. DEQUEUE ELEMENT\n");
    printf("3. SEARCH AN ELEMENT\n");
    printf("4. DISPLAY QUEUE\n");
    printf("5. EXIT\n");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    return choice;
}

void enqueue(Queue* queue){
    if( ( ((queue->rear)+1) % (queue->size) ) == (queue->front) ){
        printf("\n:( Queue is full.\n");
        return;
    }
    else if((queue->front) == -1){
        (queue->front)++;
    }
    int n;
    printf("\nEnter an element to enqueue: ");
    scanf("%d", &n);
    queue->rear = ((queue->rear)+1)%(queue->size);
    queue->array[queue->rear] = n;
    printf("\nENQUEUE SUCCESSFUL.");
    printf("\nDATA VALUE: '%d'", queue->array[queue->rear]);
    printf("\nFRONT INDEX: %d", queue->front);
    printf("\nREAR INDEX: %d\n", queue->rear);
}

int dequeue(Queue* queue){
    if(queue->rear == -1){
        printf("\n:( Queue is empty.\n");
        return -1;
    }
    int data = queue->array[queue->front];
    if(queue->front == queue->rear){
        queue->front = -1;
        queue->rear = -1;
    }
    else{
        queue->front = ((queue->front)+1)%(queue->size);
    }
    printf("\nDEQUEUE SUCCESSFUL.");
    printf("\nDATA VALUE: '%d'", data);
    printf("\nFRONT INDEX: %d", queue->front);
    printf("\nREAR INDEX: %d\n", queue->rear);
    return data;
}

int search(const Queue* queue){
    if(queue->rear == -1){
        printf("\n:( Queue is empty.\n");
        return -1;
    }
    int n;
    printf("\nEnter an element to search: ");
    scanf("%d", &n);
    printf("\nMoving from (%d -> %d)", queue->front, queue->rear);
    int i = queue->front;
    while(i != queue->rear){
        if(queue->array[i] == n){
            printf("\n:) Element found.");
            printf("\nINDEX VALUE: %d\n", i);
            return i;
        }
        i = ( (i+1) % (queue->size) );
    }
    if (queue->array[i] == n) {
        printf("\n:) Element found.");
        printf("\nINDEX VALUE: %d\n", i);
        return i;
    }
    printf("\n:( Element NOT found.\n");
    return -1;
}

void display(const Queue* queue){
    if(queue->rear == -1){
        printf("\n:( Queue is empty.\n");
        return;
    }
    printf("\nMoving from (%d -> %d)", queue->front, queue->rear);
    printf("\nQUEUE IS:\n");
    int i = queue->front;
    while(i != queue->rear){
        printf("%d,", queue->array[i]);
        i = ( (i+1) % (queue->size) );
    }
    printf("%d\n", queue->array[i]);
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);