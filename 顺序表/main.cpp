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
typedef int DataType;

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
//综合应用题函数声明
bool deleteMin(SqList& L, ElemType& value); 
void Reverse(SqList& L);                    
void del_x_1(SqList& L, ElemType x);
void del_x_2(SqList& L, ElemType x);
bool del_s_t1(SqList& L, ElemType s, ElemType t);
bool del_s_t2(SqList& L, ElemType s, ElemType t);
bool del_same(SqList& L);
void reverse_1(SqList& list, int l, int r);
void change_1(SqList& list, int m, int n);
void reverse(DataType A[], int left, int right, int arraySize);
void Exchange(DataType A[], int m, int n, int arraySize);
bool Merge(SqList a, SqList b, SqList& c);
void SearchExchangeInsert(ElemType A[], ElemType x, int length);

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
    int a[100] = { 1,3,6,9,13,16,26,37 };
    printf("长度是%d\n", L.length);

    SearchExchangeInsert(a, 2, 8);

    for (int i = 0; i < 8; i++) {//不能用 i<MaxSize ；只要输出数组已有的数据，数据个数是数组长度
        printf("data[%d]=%d\n", i,a[i]);
    }
    return 0;
}

void SearchExchangeInsert(ElemType A[], ElemType x, int length) {
    int low = 0, high = length - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (A[mid] == x) break;
        else if (A[mid] < x) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    if (A[mid] == x && mid != length - 1) {
        ElemType t = A[mid];
        A[mid] = A[mid + 1];
        A[mid + 1] = t;
    }
    if (low > high) {
        int i;
        for (i = length - 1; i > high; i--) { //下标为high的元素是比x小的元素，high+1是比x大的元素
            A[i + 1] = A[i];     // i = high+1 是最后一次循环，将下标为high+1的元素后移一位
            //当 i=high 时，不满足循环条件，跳出循环
        }
        A[i + 1] = x;		//原来下标为high+1的元素已经后移一位，此时将 x 的插在下标为 high+1 的位置
    }
}


bool Merge(SqList a, SqList b, SqList& c) {
    //将有序顺序表a、b合并为新的有序顺序表c
    //表c的长度不够！
    if (a.length + b.length > c.MaxSize) {  // 这里的大于号别写反了
        return false;
    }
    //两两比较，小的存入结果表
    int i = 0, j = 0, k = 0;
    while (i < a.length && j < b.length) {
        if (a.data[i] <= b.data[j]) {
            c.data[k++] = a.data[i++];
        }
        else {
            c.data[k++] = b.data[j++];
        }
    }
    //将剩下那个没有比较完的表存入结果表
    while (i < a.length) {
        c.data[k++] = a.data[i++];
    }
    while (j < b.length) {
        c.data[k++] = b.data[j++];
    }
    c.length = k;
    return true;
}

//王道的交换一个数组中前m和后n个元素的位置
void reverse(DataType A[], int left, int right, int arraySize) {
    //将数组A中"下标"从 left 到 right （包括left和right）的元素倒置（注意下标是从0开始的）
    if (left >= right || right > arraySize) {
        return;
    }
    int mid = (left + right) / 2;			//假设要倒置从5到10的元素，那么mid为7
    for (int i = 0; i < mid - left; i++) {	//需要将5,6,7与10,9,8交换，交换3次，i 从 0 到 (mid-left=)2 总共3次
        DataType temp = A[left + i];		//开始交换
        A[left + i] = A[right - i];
    }
}
void Exchange(DataType A[], int m, int n, int arraySize) {
    /*数组A[m+n]中，从0到m-1存放顺序表（a1,a2,...am),从m到m+n-1存放顺序表（b1,b2,...bn),算法将这两个表的位置互换*/
    reverse(A, 0, m + n - 1, arraySize);
    reverse(A, 0, n - 1, arraySize);   //将整个数组转置后，0到n-1存放的是b数组了
    reverse(A, n, m + n - 1, arraySize);
}

//网上的交换一个数组中前m和后n个元素的位置，跟第二题类似, l=left, r=right
void reverse_1(SqList& list, int l, int r) {
    //将顺序表中从 l 到 r 的元素倒置
    if (l > r || r > list.length) return;

    int mid = (l + r) / 2;
    // 注意边界
    for (int i = 0; i <= mid - l; i++) {
        swap(list.data[l + i], list.data[r - i]);
    }
}
void change_1(SqList& list, int m, int n) {
    // 注意参数
    reverse_1(list, 0, m + n - 1);
    reverse_1(list, 0, n - 1);
    reverse_1(list, n, m + n - 1);
}

bool del_same(SqList& L) {
    //删除“有序”顺序表中相同的元素，不是有序该程序无法删除相同元素
    if (L.length == 0) {
        return false;
    }
    int i, j;							//i存储第一个不相同的元素，j为工作指针
    for (i = 0, j = 1; j < L.length; j++) {
        if (L.data[i] != L.data[j]) {	//查找下一个与上个元素不同的元素
            L.data[++i] = L.data[j];	//找到后，将元素前移
        }
    }
    L.length = i + 1;
    return true;
}

bool del_s_t1(SqList& L, ElemType s, ElemType t) {
    //删除在s和t之间的元素(不包含s和t)
    if (s >= t || L.length == 0) {
        return false;
    }
    //将要保存的元素放在前面
    int k = 0;
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] <= s || L.data[i] >= t) {
            L.data[k++] = L.data[i];
        }
        //直接扔掉后面的值
    }
    L.length = k;
    return true;
}
bool del_s_t2(SqList& L, ElemType s, ElemType t) {
    //删除在s和t之间的元素(包含s和t)
    if (s >= t || L.length == 0) {
        return false;
    }

    //将要保存的元素放在前面
    int k = 0;
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] < s || L.data[i] > t) {
            L.data[k++] = L.data[i];
        }
        //直接扔掉后面的值
    }
    L.length = k;
    return true;
}

void del_x_1(SqList& L, ElemType x) {
    //删除表中值为 x 的元素
    int pos = 0;							//记录值不等于x的元素个数
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] != x) {	//
            L.data[pos++] = L.data[i];	//值不为x就将它放在数组前面并将pos加1
            //pos 使用一次后要加一，用L.data[pos]=L.data[i]; pos++ ; 更繁琐；
        }
    }
    L.length = pos;
}
void del_x_2(SqList& L, ElemType x) {
    //删除表中值为 x 的元素
    int k = 0, i = 0;					//k值记录值等于x的元素个数
    while (i < L.length) {
        if (L.data[i] == x) {
            k++;
        }
        else {
            L.data[i - k] = L.data[i];	//当前元素前移k位
        }
        L.length = L.length - k;		//数组长度递减
    }
}

//删除最小值的元素并返回该值，空出的位置由最后一个元素代替
bool deleteMin(SqList& L, ElemType& value) {
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
    for (int i = 0; i < L.length / 2; i++) {
        temp = L.data[i];
        L.data[i] = L.data[L.length - i - 1];   //注意这里的 i 和 L,length-i-1 的关系 
        L.data[L.length - i - 1] = temp;
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
    return L.data[i - 1];
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

