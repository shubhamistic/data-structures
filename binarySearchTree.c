#include <stdio.h>
#include <stdlib.h>

//Structure of a Tree.
struct Node{
    struct Node* left;
    int data;
    struct Node* right;
};
typedef struct Node Node;

//function-definitions.
void insert(Node** root);
void delete(Node** root);
void search(const Node* root);
void inorder(const Node* t);
void preorder(const Node* t);
void postorder(const Node* t);
void traverseTree(const Node* root);

int main(){
    Node* root = NULL;

    int choice;
    do {
        printf("\nSelect an operation\n");
        printf("1. INSERT NODE\n");
        printf("2. DELETE NODE\n");
        printf("3. SEARCH NODE\n");
        printf("4. TRAVERSE TREE\n");
        printf("5. EXIT\n");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                insert(&root);
                break;
            case 2:
                delete(&root);
                break;
            case 3:
                search(root);
                break;
            case 4:
                traverseTree(root);
                break;
            case 5:
                break;
            default:
                printf("\n:( Enter valid operation number.\n");
        }
    }
    while(choice!=5);

    return 0;
}

void insert(Node** root){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->left = new_node->right = NULL;
    printf("\nEnter data to the node: ");
    scanf("%d",&new_node->data);

    if(*root == NULL){
        *root = new_node;
        printf("\n:) ROOT SUCCESSFULLY INSERTED.");
        printf("\n-->ROOT VALUE: '%d'\n", (*root)->data);
        return;
    }
    Node* ptr = *root;
    Node *parentPtr;
    while(ptr) {
        if(new_node->data == ptr->data) {
            printf("\n:( INSERTION UNSUCCESSFUL.");
            printf("\n-->A NODE WITH THIS DATA ALREADY EXISTS.\n");
            return;
        }
        parentPtr = ptr;
        if (new_node->data < ptr->data)
        {ptr = ptr->left;}
        else
        {ptr = ptr->right;}
    }
    if(new_node->data < parentPtr->data)
    {parentPtr->left = new_node;}
    else
    {parentPtr->right = new_node;}

    printf("\n:) INSERTION SUCCESSFUL.");
    printf("\n-->DATA VALUE : '%d'", new_node->data);
    printf("\n-->PARENT NODE: '%d'\n", parentPtr->data);
}

void delete(Node** root){
    if(*root == NULL){
        printf("\n:( DELETION UNSUCCESSFUL.");
        printf("\n-->TREE IS EMPTY.\n");
        return;
    }

    int n;
    printf("\nEnter data value to delete: ");
    scanf("%d",&n);

    if((*root)->data == n){
        //if no child is there.
        if(((*root)->left == NULL) && ((*root)->right == NULL)) {
            free((*root));
            *root = NULL;
        }
            //if left child is there.
        else if((*root)->right == NULL){
            Node* temp = *root;
            *root = (*root)->left;
            free(temp);
        }
            //if right child is there.
        else if((*root)->left == NULL){
            Node* temp = *root;
            *root = (*root)->right;
            free(temp);
        }
            //if both left and right child are there
        else{
            Node* ptr = (*root)->left;
            if(ptr->right == NULL){
                (*root)->data = ptr->data;
                free(ptr);
                (*root)->left = NULL;
            }
            else {
                while (ptr->right->right) {
                    ptr = ptr->right;
                }
                (*root)->data = ptr->right->data;
                free(ptr->right);
                ptr->right = NULL;
            }
        }
        printf("\n:) DELETION SUCCESSFUL.");
        printf("\n-->DELETED VALUE : %d", n);
        printf("\n-->NEW ROOT VALUE: %d\n", (*root)->data);
        return;
    }
    else {
        Node *ptr = *root;
        Node *parentPtr;
        while (ptr) {
            if (n == ptr->data) {
                break;
            } else {
                parentPtr = ptr;
                if (n < ptr->data) { ptr = ptr->left; }
                else { ptr = ptr->right; }
            }
        }
        if (ptr == NULL) {
            printf("\n:( DELETION UNSUCCESSFUL.");
            printf("\n-->DATA NOT FOUND.\n");
            return;
        }
        //if no child is there.
        if(((ptr)->left == NULL) && ((ptr)->right == NULL)) {
            if(parentPtr->left == NULL){
                parentPtr->right = NULL;
            }
            else{
                if(parentPtr->left->data == n){
                    parentPtr->left = NULL;
                }
                else{
                    parentPtr->right = NULL;
                }
            }
            free(ptr);
        }
            //if left child is there.
        else if(ptr->right == NULL){
            if(parentPtr->left == NULL){
                parentPtr->right = ptr->left;
            }
            else{
                if(parentPtr->left->data == n){
                    parentPtr->left = ptr->left;
                }
                else{
                    parentPtr->right = ptr->left;
                }
            }
            free(ptr);
        }
            //if right child is there.
        else if(ptr->left == NULL){
            if(parentPtr->left == NULL){
                parentPtr->right = ptr->right;
            }
            else{
                if(parentPtr->left->data == n){
                    parentPtr->left = ptr->right;
                }
                else{
                    parentPtr->right = ptr->right;
                }
            }
            free(ptr);
        }
            //if both left and right child are there
        else{
            Node* temp = ptr->left;
            if(temp->right == NULL){
                ptr->data = temp->data;
                free(temp);
                ptr->left = NULL;
            }
            else {
                while (temp->right->right) {
                    temp = temp->right;
                }
                ptr->data = temp->right->data;
                free(temp->right);
                temp->right = NULL;
            }
        }
        printf("\n:) DELETION SUCCESSFUL.");
        printf("\n-->DELETED VALUE: '%d'.\n", n);
    }
}

void search(const Node* root){
    if(root == NULL){
        printf("\n:( TREE IS EMPTY.\n");
        return;
    }
    int n;
    printf("\nEnter data value to search: ");
    scanf("%d",&n);

    if(root->data == n){
        printf("\n:) DATA VALUE FOUND.");
        printf("\n-->AND IT IS A ROOT NODE.\n");
        return;
    }

    Node* ptr = root;
    Node* parentPtr;
    while(ptr){
        if(ptr->data == n){
            printf("\n:) DATA VALUE FOUND");
            printf("\n-->PARENT NODE: '%d'\n", parentPtr->data);
            return;
        }
        parentPtr = ptr;
        if (n < ptr->data)
        {ptr = ptr->left;}
        else
        {ptr = ptr->right;}
    }
    printf("\n:( GIVEN DATA VALUE NOT FOUND.\n");
}

void preorder(const Node* t){
    if(t != NULL){
        printf("%d,", t->data);
        preorder(t->left);
        preorder(t->right);
    }
}

void inorder(const Node* t){
    if(t != NULL){
        inorder(t->left);
        printf("%d,", t->data);
        inorder(t->right);
    }
}

void postorder(const Node* t){
    if(t != NULL){
        postorder(t->left);
        postorder(t->right);
        printf("%d,", t->data);
    }
}

void traverseTree(const Node* root){
    if(root == NULL){
        printf("\n:( Tree is empty.\n");
        return;
    }

    int choice;
    do{
        printf("\nSelect traversal option\n");
        printf("1. PREORDER\n");
        printf("2. INORDER\n");
        printf("3. POSTORDER\n");
        printf("4. BACK\n");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                preorder(root);
                break;
            case 2:
                inorder(root);
                break;
            case 3:
                postorder(root);
                break;
            case 4:
                return;
            default:
                printf("\n:( Enter valid operation number.");
        }
        printf("\n");
    }
    while(choice!=4);
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);