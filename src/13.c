// 链栈
#include "stdio.h"
#include "stdlib.h"

typedef struct linkStack {
    int data;
    struct linkStack *next;
} linkStack;

linkStack *push(linkStack *stack, int a);

linkStack *pop(linkStack *stack);

int main() {
    linkStack *stack = NULL;
    stack = push(stack, 1);
    stack = push(stack, 2);
    stack = push(stack, 3);
    stack = push(stack, 4);
    stack = pop(stack);
    stack = pop(stack);
    stack = pop(stack);
    stack = pop(stack);
    stack = pop(stack);
    return 0;
}

linkStack *push(linkStack *stack, int a) {
    linkStack *node = (linkStack *) malloc(sizeof(linkStack));
    node->data = a;
    node->next = stack;
    stack = node;
    return stack;
}

linkStack *pop(linkStack *stack) {
    printf("\n");
    if (stack) {
        linkStack *tmp = stack;
        printf("弹出元素：%d\n", tmp->data);
        stack = stack->next;
        if (stack) {
            printf("新栈顶元素：%d\n", stack->data);
        } else {
            printf("栈已空\n");
        }
        return stack;
    }
    printf("空栈\n");
    return stack;
}

