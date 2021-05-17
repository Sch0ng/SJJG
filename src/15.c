// 栈应用--括号匹配

#include "stdio.h"
#include "strings.h"

int top = -1;

void push(char *a, char elem);

void pop(char *a);

char visit(char *a);

int main() {
    char a[30];
    char *str = "{()}";
    int length = strlen(str);
    for (int i = 0; i < length; ++i) {
        if (str[i] == '(' || str[i] == '{') {
            push(a, str[i]);
        } else {
            if (str[i] == ')') {
                if (visit(a) == '(') {
                    pop(a);
                } else {
                    printf("括号不匹配1\n");
                    return 0;
                }
            } else if (str[i] == '}') {
                if (visit(a) == '{') {
                    pop(a);
                } else {
                    printf("括号不匹配2\n");
                    return 0;
                }
            } else {
                printf("括号不匹配3\n");
                return 0;
            }
        }
    }
    if (top != -1) {
        printf("括号不匹配4\n");
        return 0;
    }
    printf("括号匹配\n");
    return 0;
}

void push(char *a, char elem) {
    a[++top] = elem;
}

void pop(char *a) {
    if (top == -1) {
        return;
    }
    top--;
}

char visit(char *a) {
    if (top != -1) {
        return a[top];
    }
    return ' ';
}