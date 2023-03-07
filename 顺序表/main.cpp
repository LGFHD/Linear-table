#include <iostream>
using namespace std;

/*
// ��̬ʵ��
#define MaxSize 10

typedef struct {
    int data[MaxSize];
    int length;
}SqList;

void InitList(SqList& L) {
    //ʡ��ˢ0�����������ѭ��������Ϊ i<L.length ���Ͳ������������
    L.length = 0;
}

bool ListInsert(SqList& L, int i, int e) {
    if (i<1 || i>L.length + 1)
        return false;
    if (L.length >= MaxSize)
        return false;
    for (int j = L.length; j >= i; j--) {//�ӵ�i��Ԫ�ص����һ��Ԫ�ض�������
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool ListDelete(SqList& L, int i, int& e) {
    if (i < 1 || i>L.length)
        return false;
    e = L.data[i - 1];//�ڿ�ʼɾ������֮ǰ����Ҫɾ�������ݣ���󷵻�
    for (int j = i + 1; j <= L.length; j++) {//�ӵ�i+1��Ԫ�ؿ�ʼ��ÿһ��Ԫ����ǰ��
        L.data[j - 1 - 1] = L.data[j - 1];
    }
    L.length--;
    return true;
}
//
*/

//********************��̬ʵ��
#define InitSize 10     //���������ʼ��С
typedef int ElemType;

typedef struct {
    ElemType* data;
    int MaxSize;
    int length;
}SqList;

//��̬ʵ�֣�����������
void InitList(SqList& L);
void IncreaseSize(SqList& L, int len);      //����˳���ĳ���
bool ListInsert(SqList& L, int i, int e);
bool ListDelete(SqList& L, int i, int& e);
int GetElem(SqList& L, int i);//��λ���ң�����ֵ
int  LocateElem(SqList& L, int e);//��ֵ���ң�����λ��
bool deleteMin(SqList& L, ElemType& value);
void Reverse(SqList& L);

//********************��̬ʵ��

int main() {
    SqList L;
    InitList(L);

    //����ֵ
    for (int i = 0; i <= 5; i++) {
        L.data[i] = i + 1;
        L.length = i;
    }
    for (int i = 0; i < L.length; i++) {//������ i<MaxSize ��ֻҪ����������е����ݣ����ݸ��������鳤��
        printf("data[%d]=%d\n", i, L.data[i]);
    }
    printf("������%d\n", L.length);

     //��Ŀһ��ɾ����С
      /*int value;
        deleteMin(L, value);
        cout << value << endl;*/
    
    Reverse(L);
    for (int i = 0; i < L.length; i++) {//������ i<MaxSize ��ֻҪ����������е����ݣ����ݸ��������鳤��
        printf("data[%d]=%d\n", i, L.data[i]);
    }
    printf("������%d\n", L.length);
    return 0;
}

//ɾ����Сֵ��Ԫ�ز����ظ�ֵ���ճ���λ�������һ��Ԫ�ش���
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

//��Ч����ת�����飬�ռ临�Ӷ�Ϊ O(1)
void  Reverse(SqList& L) {
    ElemType temp;
    for (int i = 0; i < L.length/2; i++) {
        temp = L.data[i];
        L.data[i] = L.data[L.length-i-1];   //ע������� i �� L,length-i-1 �Ĺ�ϵ 
        L.data[L.length-i-1] = temp;
    }
}

//��̬ʵ�֣�����������
void InitList(SqList& L) {
    //malloc����һƬ�����Ĵ洢�ռ�
    L.data = (int*)malloc(InitSize * (sizeof(int)));//��ʼ��֮��L.dataָ��������ڴ�
    L.length = 0;
    L.MaxSize = InitSize;
}

void IncreaseSize(SqList& L, int len) {
    int* p = L.data;                     //�� *p ָ��ԭ�ռ�
    L.data = (int*)malloc((InitSize + len) * sizeof(int));//L.dataָ��������Ŀռ�
    for (int i = 0; i < L.length; i++) {
        L.data[i] = p[i];               //�����ݸ��Ƶ���������һ���ر��ʱ�䣩
    }
    L.MaxSize = L.MaxSize + len;
    free(p);//�ͷ� *p ָ��Ŀռ䣬������ *p ������ռ�ռ䣬*p �Ǿֲ����ݣ��ں����������Զ�����
}

bool ListInsert(SqList& L, int i, int e) {
    if (i<1 || i>L.length + 1)
        return false;
    if (L.length >= L.MaxSize)
        return false;
    for (int j = L.length; j >= i; j--) {//�ӵ�i��Ԫ�ص����һ��Ԫ�ض�������
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool ListDelete(SqList& L, int i, int& e) {
    if (i < 1 || i>L.length)
        return false;
    e = L.data[i - 1];//�ڿ�ʼɾ������֮ǰ����Ҫɾ�������ݣ���󷵻�
    for (int j = i + 1; j <= L.length; j++) {//�ӵ�i+1��Ԫ�ؿ�ʼ��ÿһ��Ԫ����ǰ��
        L.data[j - 1 - 1] = L.data[j - 1];
    }
    L.length--;
    return true;
}

//��λ���ң�����ֵ
int GetElem(SqList& L, int i) {
    return L.data[i-1];
}

//��ֵ���ң�����λ��
int  LocateElem(SqList& L, int e) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == e)//L.data��ָ��һ�����飬ʹ��ʱҪ�� L.data[i]
            return i + 1;
    }
    return 0;            //�˳�ѭ����˵������ʧ�ܣ���Ҫ���ص���λ��λ��û��0��
}

//��̬ʵ��

