// 后缀表达式求值
// 逆波兰表达式求值
// ! ^ + - * / ()
// 逆波兰表达式：将运算符写在运算项之后，整个表达式中不用()强调优先级

#include "stdio.h"
#include "stdlib.h"

#define MAXSIZE 50

typedef enum {
    false = 0,
    true = 1
} bool;

typedef struct {
    double data[MAXSIZE];
    int top;
} Stack_num;

void InitStack_num(Stack_num **s);

bool Push_num(Stack_num **s, double e);

bool Pop_num(Stack_num **s, double *e);

void display(Stack_num *s);

double compute_value(char *postExp);

int main() {
    char *s = "4 ! 4 2 * 10 8 - 2 ^ / +";
    double result = compute_value(s);
    printf("%lf\n", result);
}

void InitStack_num(Stack_num **s) {
    *s = (Stack_num *) malloc(sizeof(Stack_num));
    (*s)->top = -1;
}

bool Push_num(Stack_num **s, double e) {
    if ((*s)->top == MAXSIZE - 1) {
        return false;
    }
    (*s)->top += 1;
    (*s)->data[(*s)->top] = e;
    return true;
}

bool Pop_num(Stack_num **s, double *e) {
    if ((*s)->top == -1) {
        return false;
    }
    *e = (*s)->data[(*s)->top];
    (*s)->top -= 1;
    return true;
}

double compute_value(char *postExp) {
    Stack_num *num;
    int i = 1;
    double result;
    double a, b;
    double c;
    double d;

    InitStack_num(&num);

    while (*postExp != '\0') {
        printf("%c\n", *postExp);
        switch (*postExp) {
            case ' ':
                break;
            case '+':
                Pop_num(&num, &a);
                Pop_num(&num, &b);
                c = b + a;
                Push_num(&num, c);
                break;
            case '-':
                Pop_num(&num, &a);
                Pop_num(&num, &b);
                c = b - a;
                Push_num(&num, c);
                break;
            case '*':
                Pop_num(&num, &a);
                Pop_num(&num, &b);
                c = b * a;
                Push_num(&num, c);
                break;
            case '/':
                Pop_num(&num, &a);
                Pop_num(&num, &b);
                if (a != 0) {
                    c = b / a;
                    Push_num(&num, c);
                } else {
                    printf("除0错误\n");
                    exit(0);
                }
                break;
            case '^':
                Pop_num(&num, &a);
                Pop_num(&num, &b);
                if (a != 0) {
                    i = 1;
                    c = 1;
                    while (i <= a) {
                        c = c * b;
                        i++;
                    }
                } else if (b != 0) {
                    c = 1;
                } else {
                    c = 0;
                }
                Push_num(&num, c);
                break;
            case '!':
                Pop_num(&num, &a);
                c = 1;
                i = a;
                while (i != 0) {
                    c = c * i;
                    i--;
                }
                Push_num(&num, c);
                break;
            default:
                d = 0;
                while (*postExp >= '0' && *postExp <= '9') {
                    d = d * 10 + (*postExp - '0');
                    postExp++;
                }
                Push_num(&num, d);
        }
        postExp++;
        display(num);

    }
    Pop_num(&num, &result);
    return result;
}

void display(Stack_num *s) {
    int top = s->top;
    printf("top:%d ", top);

    while (top >= 0) {
        printf("%f ", s->data[top--]);
    }
    printf("\n");
}