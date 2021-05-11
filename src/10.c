// 双向循环链表

#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
    struct Node *prior; // 前驱指针域
    int data; // 数据域
    struct Node *next;  // 后继指针域
} node;

void displayNode(node *head);

node *initLine();

int main() {
    node *head = initLine();
    displayNode(head);
    return 0;
}

node *initLine() {
    node *head = (node *) malloc(sizeof(node));
    head->prior = NULL;
    head->data = 1;
    head->next = NULL;

    node *line = head;
    for (int i = 2; i <= 5; i++) {
        node *tmp = (node *) malloc(sizeof(node));
        tmp->prior = NULL;
        tmp->data = i;
        tmp->next = NULL;

        line->next = tmp;
        tmp->prior = line;
        line = line->next;
    }
    line->next = head;
    head->prior = line;
    return head;
}

void displayNode(node *head) {
    node *tmp = head;
    while (tmp->next != head) {
        printf("%d->", tmp->data);
        tmp = tmp->next;
    }
    printf("%d\n", tmp->data);
}