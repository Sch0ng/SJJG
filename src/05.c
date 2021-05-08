// 静态链表
// 静态链表的实现：可以理解成将动态链表存放节点的空间限制在一个定长的节点数组中
// 静态链表的好处：
//      1. （线性表的好处）可以用数组下标随机访问元素，快速访问
//      2. （动态链表的好处）增删节点之后不需要移动其他节点，快速增删节点
#include "stdio.h"
#include "stdlib.h"

#define maxSize 6

typedef struct {
    int data; // 数据域
    int cur;  // 游标
} component;

// 打印链表
void displayArr(component *array, int body);

// 打印整个数组的字面值
void displayArrLiteralValue(component *array);

// 构建备用链表
void reserveArr(component *array);

// 从备用链表摘取一个节点
int mallocArr(component *array);

// 初始化静态链表
int initArr(component *array);

// 往静态链表插入一个元素
// array数组 body链表的头节点在数组中的位置 location要插入的序号 num要出入的元素值
void insertArr(component *array, int body, int location, int num);

void freeArr(component *array, int k);

void deleteArr(component *array, int body, int num);

int selectElem(component *array, int body, int num);

void amendElem(component *array, int body, int oldNum, int newNum);

int main() {
    printf("----申请一块内存-----\n");
    component array[maxSize];
    displayArrLiteralValue(array);

    printf("\n");
    printf("----构建备用链表-----\n");
    reserveArr(array);
    displayArrLiteralValue(array);

    printf("\n");
    printf("----初始化链表-----\n");
    int body = initArr(array);
    displayArrLiteralValue(array);

    printf("\n");
    printf("----打印链表-----\n");
    displayArr(array, body);

    printf("\n");
    printf("----在位置2插入20-----\n");
    insertArr(array, body, 2, 20);
    displayArr(array, body);
    displayArrLiteralValue(array);

    printf("\n");
    printf("----删除元素20-----\n");
    deleteArr(array, body, 20);
    displayArr(array, body);
    displayArrLiteralValue(array);

    printf("\n");
    printf("----查找元素2的位置-----\n");
    printf("2所在的位置是：%d\n", selectElem(array, body, 2));

    printf("\n");
    printf("----将2修改成200-----\n");
    amendElem(array,body,2,200);
    displayArr(array, body);
    displayArrLiteralValue(array);
    return 0;
}

void insertArr(component *array, int body, int location, int num) {
    // 找到插入位置之前的元素
    int tBody = body;
    for (int i = 1; i < location; ++i) {
        tBody = array[tBody].cur;
    }

    int new_elem = mallocArr(array);
    array[new_elem].cur = array[tBody].cur;
    array[new_elem].data = num;
    array[tBody].cur = new_elem;
}

void deleteArr(component *array, int body, int num) {
    // 找到要删除的元素的位置

    int tBody = body;
    // 跳过头节点
    tBody = array[tBody].cur;
    int last_elem = tBody;

    while (array[tBody].data != num) {
        printf("tBody:%d data:%d\n", tBody, array[tBody].data);
        last_elem = tBody;
        tBody = array[tBody].cur;
        if (!tBody) {
            printf("没有找到要删除的元素\n");
            exit(1);
        }
    }

    array[last_elem].cur = array[tBody].cur;
    freeArr(array, tBody);
}

void freeArr(component *array, int k) {
    array[k].cur = array[0].cur;
    array[k].data = -1;
    array[0].cur = k;
}

int selectElem(component *array, int body, int num) {
    int tBody = body;
    while (array[tBody].cur != 0) {
        if (array[tBody].data == num) {
            return tBody;
        }
        tBody = array[tBody].cur;
    }
    return -1;
}

void amendElem(component *array, int body, int oldNum, int newNum) {
    int index = selectElem(array, body, oldNum);
    if (index == -1) {
        printf("静态链表中不存在要更的元素%d\n", oldNum);
        return;
    }
    array[index].data = newNum;
}

int initArr(component *array) {
    // 从备用链表摘取一个节点，作为头节点
    int body = mallocArr(array);

    int tBody = body;
    for (int i = 1; i < 4; ++i) {
        int j = mallocArr(array);
        array[tBody].cur = j;
        array[j].data = i;
        tBody = j;
    }
    array[tBody].cur = 0;
    return body;
}

/*
 * 构建备用链表
 * index:0 data:-1 cur:1
 * index:1 data:-1 cur:2
 * index:2 data:-1 cur:3
 * index:3 data:-1 cur:4
 * index:4 data:-1 cur:5
 * index:5 data:-1 cur:0
 */
void reserveArr(component *array) {
    for (int i = 0; i < maxSize; ++i) {
        array[i].data = -1;
        array[i].cur = i + 1;
    }
    array[maxSize - 1].cur = 0;
}

int mallocArr(component *array) {
    int i = array[0].cur;
    if (array[0].cur) {
        array[0].cur = array[i].cur;
    } else {
        printf("初始化失败，超出最大容量\n");
        exit(1);
    }
    return i;
}


void displayArr(component *array, int body) {
    int tbody = body;
    printf("data:%d cur:%d\n", array[tbody].data, array[tbody].cur);
    while (array[tbody].cur) {
        tbody = array[tbody].cur;
        printf("data:%2d cur:%d\n", array[tbody].data, array[tbody].cur);
    }
}

void displayArrLiteralValue(component *array) {
    int i = 0;
    for (; i < maxSize; i++) {
        printf("index:%d data:%2d cur:%d\n", i, array[i].data, array[i].cur);
    }
}