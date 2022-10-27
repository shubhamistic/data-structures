#include <stdio.h>
#include <stdlib.h>

//function-definitions;
int mainMenu();
void push();
int pop();
void display();

int main(){
    int choice;

    do {
        choice = mainMenu();
        switch (choice) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
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
