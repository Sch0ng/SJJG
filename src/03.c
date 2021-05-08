// 单链表反转
// 了解实现思想之后，不一定能写出具体的代码，多看，多想，多敲代码
// 反转方法：迭代反转、递归反转、头插法反转、就地逆置反转

#include "stdio.h"
#include "stdlib.h"

typedef struct Link {
    int elem; // 数据域
    struct Link *next; // 指针域
} link;

link *initLink();

void displayLink(link *p);

link *iteration_reverse(link *p);

link *recursive_reverse(link *p);

link *head_reverse(link *p);

link *local_reverse(link *p);

int main() {
    printf("初始化\n");
    link *p = initLink();
    displayLink(p);

    printf("利用begin、middle、end三个变量进行迭代反转\n");
    p = iteration_reverse(p);
    displayLink(p);

    printf("利用递归进行迭代反转\n");
    p = recursive_reverse(p);
    displayLink(p);

    printf("利用头插法进行迭代反转\n");
    p = head_reverse(p);
    displayLink(p);

    printf("利用就地逆置法进行迭代反转\n");
    p = local_reverse(p);
    displayLink(p);
    return 0;
}

link *initLink() {
    link *p = (link *) malloc(sizeof(link));
    link *tail = p;
    tail->elem = 1;
    int i = 2;
    for (; i <= 4; i++) {
        link *node = (link *) malloc(sizeof(link));
        node->elem = i;
        node->next = NULL;

        tail->next = node;
        tail = node;
    }
    return p;
}

link *iteration_reverse(link *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    // 第一步 初始化三个节点
    link *begin = NULL;
    link *middle = head;
    link *end = head->next;

    while (1) {
        // 第二步 middle的指针域由end改为begin
        middle->next = begin;

        // 终止条件，所有的节点反转完毕
        if (end == NULL) {
            break;
        }

        // 第三步 三个指针同步向后平移1个节点
        begin = middle;
        middle = end;
        end = end->next;
    }
    // 通过指针，返回反转后的单链表
    head = middle;
    return head;
}

link *recursive_reverse(link *head) {
    // 递归终止条件
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 找到最后一个节点作为新的头节点，即new_head
    // 因为recursive_reverse返回的new_head一直没变，所以每一层递归的时候new_head都是最后一个节点
    link *new_head = recursive_reverse(head->next);

    // 递归终止的时候，head指向倒数第二个节点
    // 每退出一层递归，head指向的节点序号减一
    head->next->next = head;
    head->next = NULL;
    return new_head;
}

link *head_reverse(link *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    link *new_head = NULL;
    link *tmp = NULL;

    while (head) {
        tmp = head;
        // 将tmp从原链表摘除
        head = head->next;
        // 将tmp插入到new_head之前
        tmp->next = new_head;
        // 移动new_head到新的节点
        new_head = tmp;
    }
    // new_head虽然是局部变量，但是值为head中已经存在的指针，在函数外部也是有效的，所以可以返回
    return new_head;
}

link *local_reverse(link *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    link *begin = head;
    link *end = head->next;
    while (end != NULL){
        // 将end从链表中摘除
        begin->next = end->next;
        // 将end移动到链表头
        end->next = head;
        head = end;
        // 调整end的指向，为反转下一个节点做准备
        end = begin->next;
    }
    return head;
}

void displayLink(link *p) {
    link *node = p;
    int i = 1;
    printf("节点:%2d 值:%2d\n", i, node->elem);
    while (node->next) {
        node = node->next;
        printf("节点:%2d 值:%2d\n", ++i, node->elem);
    }
}