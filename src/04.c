// 单链表相交：3种方法判断单链表是否相交
// 单链表只有一个指针域，所以单链表相交只有一种情况，从某个节点开始，共享之后的所有节点
// 迭代法：时间复杂度O(n^2) 能定位出相交的位置
// 比较末尾节点法：时间复杂度O(n) 只能判断是否相交，不能定位出相交的位置
// 比较短链法：时间复杂度O(n) 能定位出相交的位置

#include "stdio.h"
#include "stdlib.h"

typedef struct Link {
    int elem; // 数据域
    struct Link *next; // 指针域
} link;

typedef enum bool {
    True = 1,
    False = 0
} bool;

link *initLink(int length);

void displayLink(link *head, char *link_name);

void genIntersectLinks(link *p1, link *p2);

void genUnIntersectLinks(link *p1, link *p2);

void iterationLinksIntersect(link *p1, link *p2);

void tailLinksIntersect(link *p1, link *p2);

void shorterLinksIntersect(link *p1, link *p2);

int main() {
    printf("----构造有相交链表-----\n");
    link l1 = {};
    link l2 = {};
    genIntersectLinks(&l1, &l2);
    printf("----l1-----\n");
    displayLink(&l1, "l1");
    printf("----l2-----\n");
    displayLink(&l2, "l2");

    printf("\n");

    printf("----构造没有相交链表-----\n");
    link l3 = {};
    link l4 = {};
    genUnIntersectLinks(&l3, &l4);
    printf("----l3-----\n");
    displayLink(&l3, "l3");
    printf("----l4-----\n");
    displayLink(&l4, "l4");

    printf("\n");
    printf("----迭代法：l1&l2是否有相交-----\n");
    iterationLinksIntersect(&l1, &l2);
    printf("----迭代法：l3&l4是否有相交-----\n");
    iterationLinksIntersect(&l3, &l4);

    printf("\n");
    printf("----比较末尾节点法：l1&l2是否有相交-----\n");
    tailLinksIntersect(&l1, &l2);
    printf("----比较末尾节点法：l3&l4是否有相交-----\n");
    tailLinksIntersect(&l3, &l4);

    printf("\n");
    printf("----比较短链法：l1&l2是否有相交-----\n");
    shorterLinksIntersect(&l1, &l2);
    printf("----比较短链法：l3&l4是否有相交-----\n");
    shorterLinksIntersect(&l3, &l4);

}

link *initLink(int length) {
    link *head = (link *) malloc(sizeof(link));
    link *p = head;
    int i = 1;

    p->elem = i++;
    p->next = NULL;

    for (; i <= length; i++) {
        link *node = (link *) malloc(sizeof(link));
        node->elem = i;
        node->next = NULL;
        p->next = node;
        p = node;
    }
    return head;
}

void genIntersectLinks(link *p1, link *p2) {
    link *p = initLink(5);

    link *s1 = initLink(3);
    link *s2 = initLink(6);

    // p1在原始链表头节点之前插入一个链表
    link *ts1 = s1;
    while (ts1->next) {
        // 最后一个节点的next为NULL
        ts1 = ts1->next;
    }
    ts1->next = p;
    *p1 = *s1;

    // p2在原始链表头节点之前插入一个链表
    link *ts2 = s2;
    while (ts2->next) {
        ts2 = ts2->next;
    }
    ts2->next = p;
    *p2 = *s2;

}

void genUnIntersectLinks(link *p1, link *p2) {
    link *tp1 = initLink(4);
    link *tp2 = initLink(5);

    *p1 = *tp1;
    *p2 = *tp2;
}

void iterationLinksIntersect(link *p1, link *p2) {
    bool isIntersect = False;
    link *tp1 = p1;
    link *tp2 = NULL;

    int i = 1;
    while (tp1) {
        int j = 1;
        tp2 = p2;
        while (tp2) {
//            printf("i:%d, j:%d\n", i, j);
            if (tp1 == tp2) {
                printf("两个链表有相交，相交处位于l1:%d,l2:%d\n", i, j);
                isIntersect = True;
                break;
            }
            tp2 = tp2->next;
            j++;
        }
        if (isIntersect == True) {
            break;
        }
        tp1 = tp1->next;
        i++;
    }
    if (isIntersect == False) {
        printf("两个链表没有相交\n");
    }
}

void tailLinksIntersect(link *p1, link *p2) {
    link *tp1 = p1;
    link *tp2 = p2;

    // 定位到最后一个节点
    while (tp1->next) {
        tp1 = tp1->next;
    }

    // 定位到最后一个节点
    while (tp2->next) {
        tp2 = tp2->next;
    }

    // 比较最后一个节点，如果两个链表相交，那么最后一个节点一定是同一个节点
    if (tp1 == tp2) {
        printf("两个链表有相交\n");
    } else {
        printf("两个链表没有相交\n");
    }
}

void shorterLinksIntersect(link *p1, link *p2) {
    link *tp1 = p1;
    link *tp2 = p2;
    int len_tp1 = 0;
    int len_tp2 = 0;
    while (tp1) {
        len_tp1++;
        tp1 = tp1->next;
    }
    while (tp2) {
        len_tp2++;
        tp2 = tp2->next;
    }

    int step = 0;
    link *longer = NULL;
    link *shorter = NULL;
    if (len_tp1 > len_tp2) {
        step = len_tp1 - len_tp2;
        longer = p1;
        shorter = p2;
    } else {
        step = len_tp2 - len_tp1;
        longer = p2;
        shorter = p1;
    }

    // 跳过longer比shorter多出来的step个节点
    int t_step = step;
    while (t_step) {
        longer = longer->next;
        t_step--;
    }

    // 比较按位置逐个比较longer中剩余节点和shorter中的节点
    // 时间复杂度O(n)
    // 不仅能判断出是否相交，还能定位到相交的位置
    bool isIntersect = False;
    int i = 0;
    while (longer && shorter) {
        i++;
        if (longer == shorter) {
            printf("两个链表有相交，相交处位于l1:%d,l2:%d\n", i, i + step);
            isIntersect = True;
            break;
        }
        longer = longer->next;
        shorter = shorter->next;
    }
    if (isIntersect == False) {
        printf("两个链表没有相交\n");
    }
}

void displayLink(link *p, char *link_name) {
    int i = 1;
    while (p) {
        printf("link_name:%s, 序号:%2d, elem:%2d, addr:%p\n", link_name, i++, p->elem, p);
        p = p->next;
    }
}


