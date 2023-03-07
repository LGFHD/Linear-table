#include <iostream>
using namespace std;

/*
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
*/

//********************动态实现
#define InitSize 10     //设置数组初始大小
typedef int ElemType;

typedef struct {
    ElemType* data;
    int MaxSize;
    int length;
}SqList;

//动态实现：：函数声明
void InitList(SqList& L);
void IncreaseSize(SqList& L, int len);      //增加顺序表的长度
bool ListInsert(SqList& L, int i, int e);
bool ListDelete(SqList& L, int i, int& e);
int GetElem(SqList& L, int i);//按位查找，返回值
int  LocateElem(SqList& L, int e);//按值查找，返回位序
bool deleteMin(SqList& L, ElemType& value);
void Reverse(SqList& L);

//********************动态实现

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
    printf("长度是%d\n", L.length);

     //题目一：删除最小
      /*int value;
        deleteMin(L, value);
        cout << value << endl;*/
    
    Reverse(L);
    for (int i = 0; i < L.length; i++) {//不能用 i<MaxSize ；只要输出数组已有的数据，数据个数是数组长度
        printf("data[%d]=%d\n", i, L.data[i]);
    }
    printf("长度是%d\n", L.length);
    return 0;
}

//删除最小值的元素并返回该值，空出的位置由最后一个元素代替
bool deleteMin(SqList& L, ElemType &value) {
    if (L.length == 0) {
        return false;
    }
    value = L.data[0];
    int pos = 0;
    for (int i = 1; i < L.length; i++) {
        if (L.data[i] < value) {
            value = L.data[i];
            pos = i;
        }
    }
    L.data[pos] = L.data[L.length - 1];
    L.length--;
    return true;
}

//高效代码转置数组，空间复杂度为 O(1)
void  Reverse(SqList& L) {
    ElemType temp;
    for (int i = 0; i < L.length/2; i++) {
        temp = L.data[i];
        L.data[i] = L.data[L.length-i-1];   //注意这里的 i 和 L,length-i-1 的关系 
        L.data[L.length-i-1] = temp;
    }
}

//动态实现：：函数定义
void InitList(SqList& L) {
    //malloc申请一片连续的存储空间
    L.data = (int*)malloc(InitSize * (sizeof(int)));//初始化之后，L.data指向申请的内存
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

//按位查找，返回值
int GetElem(SqList& L, int i) {
    return L.data[i-1];
}

//按值查找，返回位序
int  LocateElem(SqList& L, int e) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == e)//L.data是指向一个数组，使用时要用 L.data[i]
            return i + 1;
    }
    return 0;            //退出循环，说明查找失败（需要返回的是位序，位序没有0）
}

//动态实现

