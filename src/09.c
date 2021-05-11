// 检测单链表是否有环

// 双层遍历：正在遍历的节点和已经遍历过的所有节点作对比，O(n^2)，可以检测出交叉点
// 差速指针：同一个标准跑道跑步的两个人，一快一满，两个人必然会擦肩而过，O(n)，只能检测出是否有环，检测不出交叉点
// 标记法：遍历过的节点做上标记，O(n)，可以检测出交叉点
// hash标记法：？

#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
    int data; // 数值域
    struct Node *next; // 指针域
} node;

// length为链表长度
// set_ring不为0时，创建带ring链表，point是ring的起始点
// set_ring为0时，创建不带ring的链表
node *initLink(int length, int set_ring, int point);

// 打印链表
// 带ring的链表打印edge个node
// 不带ring的链表打印所有node
void displayLink(node *head, int edge);

void haveRingIteration(node *head);

void haveRingStep(node *head);

void haveRingMark(node *head);

int main() {
    printf("初始化一个带ring link\n");
    node *head_has_ring = initLink(100, 1, 39);
    displayLink(head_has_ring, 200);

    printf("\n");
    printf("初始化一个不带ring link\n");
    node *head_no_ring = initLink(100, 0, 0);
    displayLink(head_no_ring, 200);

    printf("\n");
    printf("迭代法检测链表是否有环\n");
    haveRingIteration(head_has_ring);
    haveRingIteration(head_no_ring);

    printf("\n");
    printf("差速指针法检测链表是否有环\n");
    haveRingStep(head_has_ring);
    haveRingStep(head_no_ring);

    printf("\n");
    printf("标记法检测链表是否有环\n");
    haveRingMark(head_has_ring);
    haveRingMark(head_no_ring);
    return 0;
}

// 标记法检测是否有环
void haveRingMark(node *head) {
    node *tmp = head;
    while (tmp) {
        if (tmp->data < 0) {
            printf("检测到ring，ring节点的data为：%d\n", tmp->data * -1);
            return;
        }
        tmp->data *= -1;
        tmp = tmp->next;
    }
    printf("未检测到ring\n");
    return;
}

// 快慢指针
// 同一个标准跑道跑步的两个人，一快一满，两个人必然会擦肩而过
void haveRingStep(node *head) {
    node *fast_cursor = head->next;
    node *slow_cursor = head;

    int i = 1;
    while (fast_cursor) {
        printf("循环次数：%d\n", i++);
        if (fast_cursor == slow_cursor) {
            printf("检测到ring 1\n");
            return;
        }

        fast_cursor = fast_cursor->next;
        if (!fast_cursor) {
            printf("未检测到ring\n");
            return;
        }

        fast_cursor = fast_cursor->next;
        slow_cursor = slow_cursor->next;
    }
    printf("未检测到ring\n");
    return;
}

// 使用数组作为subLink仅作为演示使用
// 实际上在不知道链表长度的情况下，使用定长数组是不可取的
// 假如知道了链表长度为n，那么遍历计数如果能大于n次，即可证明链表有环
void haveRingIteration(node *head) {
    long subLink[1000] = {0};

    node *tmp = head;
    int length = 0;
    int i = 0;

    while (tmp) {
        for (i = 0; i < length; i++) {
            if (subLink[i] == (long) tmp) {
                printf("检测到ring，ring节点的data为：%d\n", tmp->data);
                return;
            }
        }
        subLink[i] = (long) tmp;
        length++;
        tmp = tmp->next;
    }
    printf("未检测到ring\n");
    return;
}

node *initLink(int length, int set_ring, int point) {
    node *head = (node *) malloc(sizeof(node));
    head->data = 1;
    head->next = NULL;

    node *point_node = head;
    node *tmp = head;
    for (int i = 2; i <= length; ++i) {
        node *t_node = (node *) malloc(sizeof(node));
        t_node->data = i;
        t_node->next = NULL;

        if (i == point) {
            point_node = t_node;
        }

        tmp->next = t_node;
        tmp = tmp->next;
    }
    if (set_ring) {
        tmp->next = point_node;
    }
    return head;
}

void displayLink(node *head, int edge) {
    node *tmp = head;
    for (int i = 1; (i <= edge) && tmp; ++i) {
        printf("index:%d, data:%d\n", i, tmp->data);
        tmp = tmp->next;
    }
}