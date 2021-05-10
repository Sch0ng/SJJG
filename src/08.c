// 循环链表
// 做算法题的第一步，弄清楚这道题到底让你干嘛。
// 而弄懂题干不是语文及格就能做到的事情，也需要多多练习，进而能熟悉专门出算法题的那帮人的习惯用语。
// 解决约瑟夫环问题
//  已知 n 个人（分别用编号 1，2，3，…，n 表示）围坐在一张圆桌周围，从编号为 k 的人开始顺时针报数，数到 m 的那个人出列；
//  他的下一个人又从 1 开始，还是顺时针开始报数，数到 m 的那个人又出列；
//  依次重复下去，直到圆桌上剩余一个人。
#include "stdio.h"
#include "stdlib.h"

typedef struct node {
    int number; // 数据域
    struct node *next; // 指针域
} person;

person *initLink(int n);

void display(person *head);

// 从k开始数，数到m出列
void findAndKill(person *head, int k, int m);

int main() {
    printf("-----初始化约瑟夫环（循环链表），8个成员-----\n");
    person *head = initLink(5);
    display(head);

    printf("-----从第三个开始，删掉数到2的-----\n");
    findAndKill(head, 3, 2);
    return 0;
}

// 从第k个人开始，k是第一个，数到第m个，然后把第m个干掉
// 再从干掉的那个的下一个开始数m个
// 直到剩下最后一个
void findAndKill(person *head, int k, int m) {
    // 找到第m个
    person *k_person = head;
    for (int i = 1; i < k; i++) {
        k_person = k_person->next;
    }

    int j = 1;
    person *death = NULL;
    person *death_prior = NULL;
    while (k_person->next != k_person) {
        printf("-------------------游戏第%d轮-------------------\n", j++);
        printf("-----剩余人员-----\n");
        display(k_person);
        printf("-----剩余人员-----\n");

        death = k_person;
        death_prior = k_person->next;
        // 找到要杀死的
        for (int i = 1; i < m; i++) {
            death = k_person->next;
        }

        // 找到death的上一个
        while (death_prior->next != death) {
            death_prior = death_prior->next;
        }

        printf("death:%d ", death->number);
        printf("death_prior:%d\n", death_prior->number);

        printf("%d被kill\n", death->number);
        printf("-------------------游戏第%d轮-------------------\n\n", j);
        k_person = death->next;
        death_prior->next = death->next;
        free(death);
    }
    printf("最终%d留在最后\n", k_person->number);
    free(k_person);
}

person *initLink(int n) {
    person *head = (person *) malloc(sizeof(person));
    head->number = 1;
    head->next = NULL;

    person *tail = head;

    for (int i = 2; i <= n; ++i) {
        person *node = (person *) malloc(sizeof(person));
        node->number = i;
        node->next = NULL;
        tail->next = node;
        tail = tail->next;
    }
    tail->next = head;
    return head;
}

void display(person *head) {
    person *tmp = head;
    int i = 1;
    while (tmp) {
        printf("index:%d number:%d\n", i++, tmp->number);
        tmp = tmp->next;
        if (tmp == head) {
            break;
        }
    }
}