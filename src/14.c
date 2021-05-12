// 栈应用--进制转换器
// 2-32进制，转为2-32进制
// 0-9代表0-9，A-Z代表10-35
// ASCII:0--48,9--57,A--65,Z--90
#include "stdio.h"
#include "strings.h"
#include "math.h"

int top = -1;

void push(char *a, char elem);

void pop(char *a);

int scaleFunOtherToTen(char *data, int system);

void scaleFunTenToOther(int num, int new_system);

int main() {
    int system = 10;
    int new_system = 32;
    char data[] = "800";
    int system_10_data = scaleFunOtherToTen(data, system);
    printf("原始数据:%s,进制:%d,转换为10进制:%d,目标进制:%d\n", data, system, system_10_data, new_system);
    scaleFunTenToOther(system_10_data, new_system);
    return 0;
}

// 十进制转其他进制
void scaleFunTenToOther(int num, int new_system) {
    char data[100];
    while (num / new_system) {
        push(data, num % new_system);
        num /= new_system;
    }
    push(data, num % new_system);
    printf("转换之后的结果为：");
    while (top != -1) {
        pop(data);
    }
    printf("\n");
}

void pop(char *a) {
    if (top == -1) {
        return;
    }
    if (a[top] >= 10) {
        printf("%c", a[top] + 55);
    } else {
        printf("%d", a[top]);
    }
    top--;
}

void push(char *a, char elem) {
    a[++top] = elem;
}

// 其他进制转10进制
int scaleFunOtherToTen(char *data, int system) {
    int k = (int) strlen(data) - 1;
    int system_10_data = 0;
    int i;
    for (i = k; i >= 0; i--) {
        int tmp;
        if (data[i] >= 48 && data[i] <= 57) {
            tmp = data[i] - 48;
        } else {
            tmp = data[i] - 55;
        }
        system_10_data += tmp * pow(system, k - i);
    }
    return system_10_data;

}