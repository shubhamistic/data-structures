#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure of a Stack.
struct Stack{
    int* int_array;
    char* char_array;
    int size;
    int top;
};
typedef struct Stack Stack;

//function-definitions;
//clarify refers to adding '$'(separator) after each unit of equation.
int validateAndClarifyEquation(char equation[]);
void printError(char error_msg[], char equation[], int n);
void addSeparator(char equation[], int n);
int isOperator(char character);
int isVariable(const char string[]);
int isDigit(const char string[]);
int checkPrecedence(char operator1, char operator2);
void convertToPrefix(const char equation[]);
int evaluate(int operand1, int operand2, char operator);
void evaluateFromPrefix(const char* equation);

int main(){
    char *equation = (char*)calloc(100, sizeof(int));

    printf("\nInput INFIX equation: ");
    fgets(equation, 100, stdin);
    equation[(strlen(equation))-1] = '\0';

    int validation_result = validateAndClarifyEquation(equation);
    if (validation_result == 1) {
        convertToPrefix(equation);
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
void pushChar(Stack* s, char c){
    if(s->top >= (s->size)-1){
        return;
    }
    s->char_array[++(s->top)] = c;
}
char popChar(Stack* s){
    if(s->top == -1){
        return '\0';
    }
    return s->char_array[(s->top)--];
}
char getCharElement(Stack* s){
    if(s->top == -1){
        return '\0';
    }
    return s->char_array[s->top];
}

void pushInt(Stack* s, int n){
    if(s->top >= (s->size)-1){
        return;
    }
    s->int_array[++(s->top)] = n;
}
int popInt(Stack* s){
    if(s->top == -1){
        return '\0';
    }
    return s->int_array[(s->top)--];
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
    Stack* validation_stack = (Stack*)malloc(sizeof(Stack));
    validation_stack->char_array = (char*)calloc(100, sizeof(int));
    validation_stack->size = 100;
    validation_stack->top = -1;

    int i=0;
    while(equation[i] != '\0'){
        if (equation[i] == '('){
            pushChar(validation_stack, '(');
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
            char result = popChar(validation_stack);
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
    if(getCharElement(validation_stack)){
        char error_msg[] = "No closing bracket for '(' found.";
        printError(error_msg, equation,i-1);
        return 0;
    }
    free(validation_stack->char_array);
    free(validation_stack);

    //reversing the equation.
    for(int j=0 ; j<(i/2) ; j++){
        char temp = equation[j];
        equation[j] = equation[i-j-1];
        equation[i-j-1] = temp;
    }
    equation++;
    equation[i-1] = '$';
    return 1;
}

//Convert to prefix---------------------------------------------------------------//
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

    if(op1 > op2){return 1;}
    return 0;
}

void convertToPrefix(const char equation[]){
    Stack* prefix_stack = (Stack*)malloc(sizeof(Stack));
    prefix_stack->char_array = (char*)calloc(100, sizeof(char));
    prefix_stack->size = 100;
    prefix_stack->top = -1;

    char* prefix_array = (char*)calloc(100, sizeof(char));
    int prefix_array_index = 0;

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
                prefix_array[prefix_array_index++] = ch[j];
                j++;
            }
            prefix_array[prefix_array_index++] = '$';
        }
        else{
            while((isOperator(getCharElement(prefix_stack))) &&
                  (checkPrecedence(getCharElement(prefix_stack), ch[0])))
            {
                char operator = popChar(prefix_stack);
                prefix_array[prefix_array_index++] = operator;
                prefix_array[prefix_array_index++] = '$';
            }
            if(ch[0] != '('){
                pushChar(prefix_stack, ch[0]);
            }
            else{
                while(getCharElement(prefix_stack) != ')'){
                    prefix_array[prefix_array_index++] = popChar(prefix_stack);
                    prefix_array[prefix_array_index++] = '$';
                }
                popChar(prefix_stack);
            }
        }
        i++;
    }
    while(getCharElement(prefix_stack)){
        char operator = popChar(prefix_stack);
        prefix_array[prefix_array_index++] = operator;
        prefix_array[prefix_array_index++] = '$';
    }

    printf("\nPREFIX FORM:-\n");
    for(int j = strlen(prefix_array)-1 ;j>=0 ; j--){
        if(prefix_array[j] != '$'){
            printf("%c", prefix_array[j]);
        }
    }
    printf("\n");

    free(prefix_stack->char_array);
    free(prefix_stack);

    evaluateFromPrefix(prefix_array);
    free(prefix_array);
}

//evaluating from prefix array----------------------------------------------------//
int evaluate(int operand1, int operand2, char operator){
    if(operator == '+'){
        return (operand1 + operand2);
    }
    else if(operator == '-'){
        return (operand1 - operand2);
    }
    else if(operator == '*'){
        return (operand1 * operand2);
    }
    else if(operator == '/'){
        printf("\nWarning: Dividing two operands will cause");
        printf("\ndigit loss after the decimal point.\n");
        return (operand1/operand2);
    }
    else if(operator == '^'){
        int result = 1;
        for(int i = 0 ; i < operand2 ; i++){
            result = result*operand1;
        }
        return result;
    }
    else{
        return 0;
    }
}

void evaluateFromPrefix(const char* equation){
    Stack* prefix_stack = (Stack*)malloc(sizeof(Stack));
    prefix_stack->int_array = (int*)malloc(sizeof(equation));
    prefix_stack->size = 10;
    prefix_stack->top = -1;

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
            pushInt(prefix_stack, num);
        }
        else if(isVariable(ch)){
            printf("\nEnter Value of '%s' in the equation: ", ch);
            scanf("%d", &num);
            pushInt(prefix_stack, num);
        }
        else if (isOperator(ch[0])){
            int operand1 = popInt(prefix_stack);
            int operand2 = popInt(prefix_stack);
            pushInt(prefix_stack, evaluate(operand1, operand2, ch[0]));
        }
    }
    printf("\nResult after evaluation is: %d\n", popInt(prefix_stack));
    free(prefix_stack->int_array);
    free(prefix_stack);
}

//Author - Shubham, github-url: "github.com/shubhamistic";