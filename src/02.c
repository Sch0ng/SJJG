// 单链表
#include "stdio.h"
#include "stdlib.h"

/**
 * 头指针：一个普通的指针，永远指向链表的第一个节点
 * 头节点：一个不存任何数据的空节点，不必须，方便链表的使用
 * 首元节点：链表中第一个存有数据的节点
 *
 * 从实际的code来看，带头节点处理起来比较方便
 */

typedef struct Link {
    int elem; // 数据域
    struct Link *next; // 指针域，指向直接后继元素
} link;

// 初始化链表
link *initLink();

// 打印链表
void displayLink(link *p);

// 插入 seq属于[1, n]
link *insertLink(link *p, int elem, int seq);

// delete element
link *delElem(link *p, int seq);

// select element
int selectElement(link *p, int elem);

// amend element
link *amendElement(link *p, int newElem, int seq);

int main() {
    printf("初始化Link\n");
    link *p = initLink();
    displayLink(p);

    printf("\n-------------插入测试-------------");
    printf("\nseq=5，插入101\n");
    p = insertLink(p, 105, 5);
    displayLink(p);

    printf("\nseq=1，插入100\n");
    p = insertLink(p, 100, 1);
    displayLink(p);

    printf("\n-------------删除测试-------------");
    printf("\n删除seq=1\n");
    p = delElem(p, 1);
    displayLink(p);

    printf("\n删除seq=5\n");
    p = delElem(p, 3);
    displayLink(p);

    printf("\n-------------查找测试-------------");
    displayLink(p);
    printf("\n查找4，查找结果：%d\n", selectElement(p, 4));
    printf("\n查找105，查找结果：%d\n", selectElement(p, 105));

    printf("\n-------------修改测试-------------");
    printf("\nseq=1，改为30\n");
    p = amendElement(p, 30, 1);
    displayLink(p);

    printf("\nseq=10，改为20\n");
    p = amendElement(p, 20, 10);
    displayLink(p);
}

// 初始化链表，链表中的元素为{1, 2, 3, 4}
link *initLink() {
    link *p = (link *) malloc(sizeof(struct Link));
    link *tail = p;
    for (int i = 1; i < 5; ++i) {
        // 初始化一个节点
        link *a = (link *) malloc(sizeof(struct Link));
        a->elem = i;
        a->next = NULL;

        // 将新节点接到list的末尾
        tail->next = a;

        // 循环赋值，重置尾指针
        tail = tail->next;
    }
    return p;
}

// display
void displayLink(link *p) {
    printf("打印List\n");
    link *cursor = p;
    while (cursor->next) {
        cursor = cursor->next;
        printf("%d ", cursor->elem);
    }
    printf("\n");
}

// 插入
link *insertLink(link *p, int elem, int seq) {
    link *cursor = p;
    // 1. 定位到要插入的位置 cursor为seq位置的上一个元素
    for (int i = 1; i < seq; ++i) {
        cursor = cursor->next;

        if (cursor == NULL) {
            printf("插入位置错误\n");
            return p;
        }
    }

    // 2. 创建新的node
    link *newNode = (link *) malloc(sizeof(link));
    newNode->elem = elem; // 设置值域
    newNode->next = cursor->next;  // 将指针域指向下一个元素

    // 3. 设置前置元素的指针域
    cursor->next = newNode;

    return p;
}

// delete element
link *delElem(link *p, int seq) {
    link *cursor = p;

    // 1. 定位到要插入的位置 cursor为seq位置的上一个元素
    for (int i = 1; i < seq; ++i) {
        cursor = cursor->next;
        if (cursor == NULL) {
            printf("删除的位置错误\n");
            return p;
        }
    }
    // 2. 防止删除的指针丢失
    link *del = cursor->next;

    // 3. 前置结点的指针域跳过当前要删的元素指向后置结点
    cursor->next = cursor->next->next;

    // 手动释放结点，防止内存泄漏
    free(del);
    return p;
}

// select element
int selectElement(link *p, int elem) {
    link *cursor = p;
    int i = 1;

    // 跳过头结点
    while (cursor->next) {
        cursor = cursor->next;
        if (cursor->elem == elem) {
            return i;
        }
        i++;
    }
    return -1;
}

// amend element
link *amendElement(link *p, int newElem, int seq) {
    link *cursor = p;
    for (int i = 1; i < seq; ++i) {
        cursor = cursor->next;
        if (cursor == NULL) {
            printf("修改位置错误\n");
            return p;
        }
    }
    cursor->next->elem = newElem;
    return p;
}
