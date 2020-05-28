#include <stdlib.h>
#include <stdio.h>
#define INIT_SIZE       (10)

typedef struct stack_t stack_t;
void error(){
    printf("out of memory!\n");
    exit(1);
}
struct stack_t {
    int size;
    int currSize;
    int* a;
};

stack_t* new_stack(){
    stack_t* stack;
    stack = malloc(sizeof(stack_t));
    if(stack == NULL)
        error();
    stack->a = malloc(sizeof(int) * INIT_SIZE);
    if (stack->a == NULL)
        error();

    stack->currSize = -1;
    stack->size = INIT_SIZE;
    return stack;
}

void push(stack_t* stack, int i){
    if(stack->currSize == stack->size){
        int* save = stack->a;
        stack->a = realloc(stack->a, sizeof(int) * stack->currSize * 2);
        if (stack->a == NULL){
            stack->a = save;
            error();
        }
    }
    stack->a[++stack->currSize] = i;
}

int pop(stack_t* stack){
    if (stack->currSize < 0){
        error();
    }
    
    stack->currSize--; 
    return stack->a[stack->currSize + 1];

}

int top(stack_t* stack){
    if (stack->currSize < 0){
        error();
    }
    return stack->a[0];
}

void free_stack(stack_t* stack){
    free(stack->a);
    free(stack);
}

int main(void){
    stack_t* stack = new_stack();
    push(stack, 11);
    push(stack, 13);
    push(stack, 44);
    int i, k, l;
    i = pop(stack);
    k = pop(stack);
    l = pop(stack);
    printf("%d, %d, %d\n", i, k, l);
    free_stack(stack);
}
