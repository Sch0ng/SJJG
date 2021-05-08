// 双向链表
// 解决单链表查找的时候只能"从前往后"不能"从后往前"的问题
#include "stdio.h"
#include "stdlib.h"

typedef struct line {
    struct line *prior; // 直接前驱指针域
    int data; // 数据域
    struct line *next; // 直接后继指针域
} line;

line *initLine(line *head);

void displayLine(line *head);

line *insertLine(line *head, int data, int location);

line *deleteElem(line *head, int data);

int selectElem(line *head, int data);

line *amendElem(line *head, int location, int data);

int main() {
    printf("----初始化一个双向链表-----\n");
    line *head = NULL;
    head = initLine(head);
    displayLine(head);

    printf("\n");
    printf("----在3位置insert一个30-----\n");
    head = insertLine(head, 30, 3);
    displayLine(head);

    printf("\n");
    printf("----删除值30-----\n");
    head = deleteElem(head, 30);
    displayLine(head);

    printf("\n");
    printf("----查找值2-----\n");
    printf("2的序号为%d\n", selectElem(head, 2));
    displayLine(head);

    printf("\n");
    printf("----将第三个节点的值改为33-----\n");
    head = amendElem(head, 3, 33);
    displayLine(head);

    return 0;
}

line *amendElem(line *head, int location, int data) {
    line *tmp = head;
    for (int i = 1; i < location; ++i) {
        tmp = tmp->next;
    }
    tmp->data = data;
    return head;
}

int selectElem(line *head, int data) {
    line *tmp = head;
    int i = 1;
    while (tmp) {
        if (tmp->data == data) {
            return i;
        }
        i++;
        tmp = tmp->next;
    }
    return -1;
}

line *deleteElem(line *head, int data) {
    line *tmp = head;
    while (tmp) {
        if (tmp->data == data) {
            tmp->next->prior = tmp->prior;
            tmp->prior->next = tmp->next;
            free(tmp);
            return head;
        }
        tmp = tmp->next;
    }
    printf("双向链表中未找到要删除的值%d\n", data);
    return head;
}

line *insertLine(line *head, int data, int location) {
    line *node = (line *) malloc(sizeof(line));
    node->prior = NULL;
    node->next = NULL;
    node->data = data;

    if (location == 1) {
        node->next = head;
        head->prior = node;
        head = node;
        return head;
    }

    // 找到插入位置的前一个节点
    line *list = head;
    for (int i = 1; i < location - 1; ++i) { // 遍历条件需要仔细琢磨，没有道理可言，能实现目的即可
        list = list->next;
    }

    // 插入位置是链表末尾
    if (list->next == NULL) {
        node->prior = list;
        list->next = node;
        return head;
    }

    // 插入位置在链表中间
    list->next->prior = node;
    node->next = list->next;
    list->next = node;
    node->prior = list;

    return head;
}

line *initLine(line *head) {
    head = (line *) malloc(sizeof(line));
    head->prior = NULL;
    head->next = NULL;
    head->data = 1;

    line *list = head;
    for (int i = 2; i <= 5; ++i) {
        line *node = (line *) malloc(sizeof(line));
        node->prior = NULL;
        node->next = NULL;
        node->data = i;

        list->next = node;
        node->prior = list;
        list = node;
    }
    return head;
}

void displayLine(line *head) {
    line *tmp = head;
    int i = 1;
    while (tmp) {
        if (tmp->next == NULL) {
            printf("(seq:%d data:%d)\n", i, tmp->data);
        } else {
            printf("(seq:%d data:%d)  <->  ", i, tmp->data);
        }
        tmp = tmp->next;
        i++;
    }
}