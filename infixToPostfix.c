#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure stack for storing character.
struct stack{
    char* array;
    int size;
    int top;
};
typedef struct stack stack;

//structure stack for storing integer.
struct Intstack{
    int array[10];
    int size;
    int top;
};
typedef struct Intstack Intstack;

//function-definitions;
//clarify refers to adding '$'(separator) after each unit of equation.
int validateAndClarifyEquation(char equation[]);
void printError(char error_msg[], char equation[], int n);
void addSeparator(char equation[], int n);
int isOperator(char character);
int isVariable(const char string[]);
int isDigit(const char string[]);
int checkPrecedence(char operator1, char operator2);
void convertToPostfix(const char equation[]);
int evaluate(int operand2, int operand1, char operator);
void evaluateFromPostfix(const char equation[]);

int main(){
    char *equation = (char *) calloc(100, sizeof(int));

    printf("\nInput INFIX equation: ");
    fgets(equation, 100, stdin);
    equation[(strlen(equation))-1] = '\0';

    int validation_result = validateAndClarifyEquation(equation);
    if (validation_result == 1) {
        convertToPostfix(equation);
    }

    return 0;
}

//is-true or false----------------------------------------------------------------//
int isOperator(char character){
    if((character == '+') || (character == '-') ||
       (character == '*') || (character == '/') ||
       (character == '^'))
    {
        return 1;
    }
    return 0;
}

int isVariable(const char string[]){
    int i=0;
    if(((string[i] >= 65) && (string[i] <= 90)) ||
       ((string[i] >= 97) && (string[i] <= 122)))
    {
        while(((string[i] >= 65) && (string[i] <= 90)) ||
              ((string[i] >= 97) && (string[i] <= 122)) ||
              ((string[i] >= 48) && (string[i] <= 57)))
        {
            i++;
        }
        if(string[i] == '\0'){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

int isDigit(const char string[]){
    int i=0;
    while((string[i] >= 48) && (string[i] <= 57))
    {
        i++;
    }
    if(string[i] == '\0'){
        return 1;
    }
    return 0;
}

//stack operations----------------------------------------------------------------//
void push(stack* stack_array, char c){
    if(stack_array->top >= (stack_array->size)-1){
        return;
    }
    stack_array->array[++(stack_array->top)] = c;
}

void pushInt(Intstack* stack_array, int n){
    if(stack_array->top >= (stack_array->size)-1){
        return;
    }
    stack_array->array[++(stack_array->top)] = n;
}

char pop(stack* stack_array){
    if(stack_array->top == -1){
        return '\0';
    }
    return stack_array->array[(stack_array->top)--];
}

int popInt(Intstack* stack_array){
    if(stack_array->top == -1){
        return '\0';
    }
    return stack_array->array[(stack_array->top)--];
}

char getElement(stack* stack_array){
    if(stack_array->top == -1){
        return '\0';
    }
    return stack_array->array[stack_array->top];
}

//Equation validation and clarification-------------------------------------------//
void printError(char error_msg[], char equation[], int n){
    printf("\n%s", error_msg);
    printf("\n");
    int count = 0;
    for(int i = 0 ; equation[i]!='\0' ; i++){
        if(equation[i] == '$'){
            count++;
            continue;
        }
        printf("%c", equation[i]);
    }
    printf("\n");
    for(int i = 0 ; i<n-count ; i++){
        printf(" ");
    }
    printf("^\n");
}

void addSeparator(char equation[], int n){
    for (int i = 99; i > n; i--) {
        equation[i] = equation[i - 1];
    }
    equation[n] = '$';
}

int validateAndClarifyEquation(char equation[]){
    stack* validation_array = (stack*)malloc(sizeof(stack));
    validation_array->array = (char*)calloc(100, sizeof(int));
    validation_array->size = 100;
    validation_array->top = -1;

    int i=0;
    while(equation[i] != '\0'){
        if (equation[i] == '('){
            push(validation_array, '(');
            addSeparator(equation, ++i);
        }
        else if((equation[i] >= 48) && (equation[i] <= 57)){
            while((equation[i] >= 48) && (equation[i] <= 57)){
                i++;
            }
            if(isOperator(equation[i]) || (equation[i] == ')') ||
               (equation[i] == '(') || (equation[i] == '\0'))
            {
                addSeparator(equation, i);
            }
            else if(((equation[i] >= 65) && (equation[i] <= 90)) ||
                    ((equation[i] >= 97) && (equation[i] <= 122)))
            {
                char error_msg[] = "Unexpected Data Value Encountered.";
                printError(error_msg, equation,i);
                return 0;
            }
        }
        else if(((equation[i] >= 65) && (equation[i] <= 90)) ||
                ((equation[i] >= 97) && (equation[i] <= 122)))
        {
            while(((equation[i] >= 65) && (equation[i] <= 90)) ||
                  ((equation[i] >= 97) && (equation[i] <= 122)) ||
                  ((equation[i] >= 48) && (equation[i] <= 57)))
            {
                i++;
            }
            if(isOperator(equation[i]) || (equation[i] == ')') ||
               (equation[i] == '(') || (equation[i] == '\0'))
            {
                addSeparator(equation, i);
            }
            else if(((equation[i] >= 65) && (equation[i] <= 90)) ||
                    ((equation[i] >= 97) && (equation[i] <= 122)))
            {
                char error_msg[] = "Unexpected Variable Name Encountered.";
                printError(error_msg, equation, i);
                return 0;
            }
        }
        else if(isOperator(equation[i])){
            if(isOperator(equation[i+1])){
                char error_msg[] = "Unexpected Operator Encountered.";
                printError(error_msg, equation, i+1);
                return 0;
            }
            else if(((equation[i+1] >= 65) && (equation[i+1] <= 90)) ||
                    ((equation[i+1] >= 97) && (equation[i+1] <= 122)) ||
                    ((equation[i+1] >= 48) && (equation[i+1] <= 57)) ||
                    (equation[i+1] == '(') || (equation[i+1] == ')'))
            {
                addSeparator(equation, ++i);
            }
            else {
                char error_msg[] = "Unexpected variable or value given after operator.";
                printError(error_msg, equation, i);
                return 0;
            }
        }
        else if(equation[i] == ' '){
            char error_msg[] = "Spaces are not allowed.\n";
            printError(error_msg, equation, i);
            return 0;
        }
        else if(equation[i] == ')'){
            char result = pop(validation_array);
            if(result == '\0'){
                char error_msg[] = "No opening bracket for ')' found.";
                printError(error_msg, equation, i);
                return 0;
            }
            else{
                addSeparator(equation, ++i);
            }
        }
        else{
            char error_msg[] = "Unknown Character Encountered.";
            printError(error_msg, equation, i);
            return 0;
        }
        i++;
    }
    if(getElement(validation_array)){
        char error_msg[] = "No closing bracket for '(' found.";
        printError(error_msg, equation,i-1);
        return 0;
    }

    free(validation_array->array);
    free(validation_array);
    return 1;
}

//Convert to postfix--------------------------------------------------------------//
int checkPrecedence(char operator1, char operator2){
    int op1;
    if(operator1 == '^'){op1 = 3;}
    else if((operator1 == '*') || (operator1 == '/')){op1 = 2;}
    else if((operator1 == '+') || (operator1 == '-')){op1 = 1;}
    else{return 0;}

    int op2;
    if(operator2 == '^'){op2 = 3;}
    else if((operator2 == '*') || (operator2 == '/')){op2 = 2;}
    else if((operator2 == '+') || (operator2 == '-')){op2 = 1;}
    else{return 0;}

    if(op1 >= op2){return 1;}
    return 0;
}

void convertToPostfix(const char equation[]){
    stack* postfix_stack = (stack*)malloc(sizeof(stack));
    postfix_stack->array = (char*)calloc(100, sizeof(char));
    postfix_stack->size = 100;
    postfix_stack->top = -1;

    char* postfix_array = (char*)calloc(100, sizeof(char));
    int postfix_array_index = 0;

    int i = 0;
    while(equation[i] != '\0'){
        char ch[10];
        int ch_counter = 0;
        while((equation[i] != '$') && (equation[i] != '\0')){
            ch[ch_counter++] = equation[i];
            i++;
        }
        ch[ch_counter++] = '\0';
        ch_counter = 0;

        if(isDigit(ch) || isVariable(ch)){
            int j = 0;
            while(ch[j]){
                postfix_array[postfix_array_index++] = ch[j];
                j++;
            }
            postfix_array[postfix_array_index++] = '$';
        }
        else{
            while((isOperator(getElement(postfix_stack))) &&
                  (checkPrecedence(getElement(postfix_stack), ch[0])))
            {
                char operator = pop(postfix_stack);
                postfix_array[postfix_array_index++] = operator;
                postfix_array[postfix_array_index++] = '$';
            }
            if(ch[0] != ')'){
                push(postfix_stack, ch[0]);
            }
            else{
                while(getElement(postfix_stack) != '('){
                    postfix_array[postfix_array_index++] = pop(postfix_stack);
                    postfix_array[postfix_array_index++] = '$';
                }
                pop(postfix_stack);
            }
        }
        i++;
    }
    while(getElement(postfix_stack)){
        char operator = pop(postfix_stack);
        postfix_array[postfix_array_index++] = operator;
        postfix_array[postfix_array_index++] = '$';
    }

    printf("\nPOSTFIX FORM:-\n");
    for(int j = 0 ; postfix_array[j] ; j++){
        if(postfix_array[j] != '$'){
            printf("%c", postfix_array[j]);
        }
    }
    printf("\n");

    free(postfix_stack->array);
    free(postfix_stack);

    evaluateFromPostfix(postfix_array);
    free(postfix_array);
}

//evaluating from postfix array-----------------------------------------------------//
int evaluate(int operand2, int operand1, char operator){
    if(operator == '+'){
        return (operand2 + operand1);
    }
    else if(operator == '-'){
        return (operand2 - operand1);
    }
    else if(operator == '*'){
        return (operand2 * operand1);
    }
    else if(operator == '/'){
        printf("\nWarning: Dividing two operands will cause");
        printf("\ndigit loss after the decimal point.\n");
        return (operand2/operand1);
    }
    else if(operator == '^'){
        int result = 1;
        for(int i = 0 ; i < operand1 ; i++){
            result = result*operand2;
        }
        return result;
    }
    else{
        return 0;
    }
}

void evaluateFromPostfix(const char equation[]){
    Intstack* postfix_stack = (Intstack*)malloc(sizeof(Intstack));
    postfix_stack->size = 10;
    postfix_stack->top = -1;

    for(int i = 0 ; equation[i] ; i++){
        char ch[10];
        int ch_counter = 0;
        while((equation[i] != '$') && (equation[i] != '\0')){
            ch[ch_counter++] = equation[i];
            i++;
        }
        ch[ch_counter++] = '\0';
        ch_counter = 0;

        int num = 0;
        if(isDigit(ch)){
            for(int j = 0 ; ch[j]; j++){
                num = num * 10 + (ch[j] - 48);
            }
            pushInt(postfix_stack, num);
        }
        else if(isVariable(ch)){
            printf("\nEnter Value of '%s' in the equation: ", ch);
            scanf("%d", &num);
            pushInt(postfix_stack, num);
        }
        else if (isOperator(ch[0])){
            int operand1 = popInt(postfix_stack);
            int operand2 = popInt(postfix_stack);
            pushInt(postfix_stack, evaluate(operand2, operand1, ch[0]));
        }
    }
    printf("\nResult after evaluation is: %d\n", popInt(postfix_stack));

    free(postfix_stack);
}

//By - Shubham 219301072 B.Tech Sec-3C (CSE);