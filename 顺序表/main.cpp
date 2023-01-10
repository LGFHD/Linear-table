#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// 静态实现
#define MaxSize 10

typedef struct {
    int data[MaxSize];
    int length;
}SqList;

void InitList(SqList& L) {
    //省略刷0，下面输出的循环条件设为 i<L.length ；就不会输出脏数据
    L.length = 0;
}

bool ListInsert(SqList& L, int i, int e) {
    if (i<1 || i>L.length + 1)
        return false;
    if (L.length >= MaxSize)
        return false;
    for (int j = L.length; j >= i; j--) {//从第i个元素到最后一个元素都往后移
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool ListDelete(SqList& L, int i, int& e) {
    if (i < 1 || i>L.length)
        return false;
    e = L.data[i - 1];//在开始删除操作之前保存要删除的数据，最后返回
    for (int j = i + 1; j <= L.length; j++) {//从第i+1个元素开始，每一个元素往前移
        L.data[j - 1 - 1] = L.data[j - 1];
    }
    L.length--;
    return true;
}
//

/*动态实现
#define InitSize 10

typedef struct {
    int* data;
    int MaxSize;
    int length;
}SqList;

void InitList(SqList& L) {
    //malloc申请一片连续的存储空间
    L.data = (int*)malloc(InitSize*(sizeof(int)));//初始化之后，L.data指向的是数组？
    L.length = 0;
    L.MaxSize = InitSize;
}

void IncreaseSize(SqList& L, int len) {
    int* p = L.data;                     //将 *p 指向原空间
    L.data = (int*)malloc((InitSize + len) * sizeof(int));//L.data指向新申请的空间
    for (int i = 0; i < L.length; i++) {
        L.data[i] = p[i];               //将数据复制到新区域（这一步特别耗时间）
    }
    L.MaxSize = L.MaxSize + len;
    free(p);//释放 *p 指向的空间，而不是 *p 自身所占空间，*p 是局部数据，在函数结束后自动销毁
}

bool ListInsert(SqList& L, int i, int e) {
    if (i<1 || i>L.length + 1)
        return false;
    if (L.length >= L.MaxSize)
        return false;
    for (int j = L.length; j >= i; j--) {//从第i个元素到最后一个元素都往后移
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool ListDelete(SqList& L, int i, int& e) {
    if (i < 1 || i>L.length)
        return false;
    e = L.data[i - 1];//在开始删除操作之前保存要删除的数据，最后返回
    for (int j = i + 1; j <= L.length; j++) {//从第i+1个元素开始，每一个元素往前移
        L.data[j - 1 - 1] = L.data[j - 1];
    }
    L.length--;
    return true;
}
动态实现*/


int main() {
    SqList L;
    InitList(L);

    //赋初值
    for (int i = 0; i <= 5; i++) {
        L.data[i] = i + 1;
        L.length = i;
    }
    for (int i = 0; i < L.length; i++) {//不能用 i<MaxSize ；只要输出数组已有的数据，数据个数是数组长度
        printf("data[%d]=%d\n", i, L.data[i]);
    }
    cout << "长度是" << L.length << endl;

    //删除
    int e = -1;
    if (ListDelete(L, 3, e)) {
        cout << "删除的是" << e << endl;
    }
    else {
        cout << "位序不合法" << endl;
    }
    cout << "删除后长度是" << L.length << endl;

    //插入
    ListInsert(L, 3, 10);
    for (int i = 0; i < L.length; i++) {//不能用 i<MaxSize ；只要输出数组已有的数据，数据个数是数组长度
        printf("data[%d]=%d\n", i, L.data[i]);
    }
    cout << "插入后长度是" << L.length << endl;

    return 0;

}