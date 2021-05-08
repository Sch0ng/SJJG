// 顺序表
// 顺序表优势：访问速度快（查询和修改）、实现简单
// 顺序表劣势：增删效率低、固定长度、内存利用率低

#include "stdio.h"
#include "stdlib.h"

#define Size 6

/**
 * seq 线性表的序号从1起始
 * index 数组的下标从0起始
 */

// 定义顺序表
typedef struct Table {
    int *head; // 指针，指向存储数据的数组
    int length; // 长度：顺序表已经存储的元素数
    int size; // 容量：顺序表总共可以存储的元素数
} table;

// 打印顺序表
void displayTable(table *t);

// 初始化顺序表
table initTable();

// 插入 elem为插入的数据 seq为插入的位置
table addTable(table t, int elem, int seq);

// 删除
table delTable(table t, int seq);

// 查找
int selectTable(table t, int elem);

// 修改
int amendTable(table *t, int elem, int newElem);

int main() {
    table t = initTable();
    for (int i = 0; i < Size - 3; ++i) {
        t.head[i] = i * 2;
        t.length++;
    }
    displayTable(&t);
    printf("\n-------------插入测试-------------");
    printf("在开头插入100\n");
    t = addTable(t, 100, 1);
    displayTable(&t);

    printf("\n");
    printf("在2位置插入-10\n");
    t = addTable(t, -10, 2);
    displayTable(&t);

    printf("\n");
    printf("在末尾插入-20\n");
    t = addTable(t, -20, t.length + 1);
    displayTable(&t);

    printf("\n");
    printf("在末尾插入-30\n");
    t = addTable(t, -30, t.length + 1);
    displayTable(&t);

    printf("\n");
    printf("在1位置插入-10\n");
    t = addTable(t, -10, 1);
    displayTable(&t);

    printf("\n-------------删除测试-------------");
    printf("del开头\n");
    t = delTable(t, 1);
    displayTable(&t);

    printf("\n");
    printf("del末尾\n");
    t = delTable(t, t.length);
    displayTable(&t);

    printf("\n");
    printf("del 2\n");
    t = delTable(t, 2);
    displayTable(&t);

    printf("\n-------------查找-------------");
    printf("查找3：%d\n", selectTable(t, 3));
    printf("查找2：%d\n", selectTable(t, 2));
    printf("查找100：%d\n", selectTable(t, 100));
    printf("查找-20：%d\n", selectTable(t, -20));

    printf("\n-------------替换-------------");
    printf("-20替换成22\n");
    amendTable(&t, -20, 22);
    displayTable(&t);
    return 0;
}

// 初始化顺序表
table initTable() {
    table t;
    t.head = (int *) malloc(Size * sizeof(int));
    if (!t.head) {
        printf("初始化失败");
        exit(0);
    }
    t.length = 0;
    t.size = Size;
    return t;
}

// 插入
table addTable(table t, int elem, int seq) {
    // 检查seq是否合法，seq最小为1 最大为length+1
    if (seq < 1 || seq > t.length + 1) {
        printf("插入位置错误\n");
        exit(0);
    }

    // 检查是否有充足的空间
    if (t.length == t.size) {
        printf("触发内存重新分配\n");
        t.head = (int *) realloc(t.head, (t.size + 1) * sizeof(int));
        if (!t.head) {
            printf("存储分配失败\n");
            exit(0);
        }
        t.size++;
    }

    // 后移插入位置的后继元素，从 length 到 seq
    // 设置边界的时候有两个障碍
    //    1. 遍历从谁到谁，画草图可以很明显的分析出来
    //    2. seq跟index之间存在一层转换关系
    for (int i = t.length; i >= seq; i--) {
        // seq 转 index 需要 -1
        t.head[i] = t.head[i - 1];
    }

    // 后移完成后，将elem放入seq
    t.head[seq - 1] = elem;
    t.length++;

    return t;
}

// 删除
table delTable(table t, int seq) {
    // seq异常判断，处于1到length之间
    if (seq < 1 || seq > t.length) {
        printf("删除位置错误\n");
        exit(0);
    }
    // 移动，从seq 到 length - 1
    for (int i = seq; i < t.length; i++) {
        // seq 转 index 需要 -1
        t.head[i - 1] = t.head[i];
    }

    // 更新长度
    t.length--;
    return t;
}

// 查找
int selectTable(table t, int elem) {
    for (int i = 0; i < t.length; i++) {
        if (t.head[i] == elem) {
            return i + 1;
        }
    }
    return -1;
}

int amendTable(table *t, int elem, int newElem) {
    int seq = selectTable(*t, elem);
    if (seq != -1) {
        t->head[seq - 1] = newElem;
        return 0;
    }
    return -1;
}

// 打印顺序表
void displayTable(table *t) {
    printf("size:%d length:%d \nelements: ", t->size, t->length);
    for (int i = 0; i < t->length; ++i) {
        printf("%d ", t->head[i]);
    }
    printf("\n");
}



