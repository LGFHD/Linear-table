#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

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

/*��̬ʵ��
#define InitSize 10

typedef struct {
    int* data;
    int MaxSize;
    int length;
}SqList;

void InitList(SqList& L) {
    //malloc����һƬ�����Ĵ洢�ռ�
    L.data = (int*)malloc(InitSize*(sizeof(int)));//��ʼ��֮��L.dataָ��������飿
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
��̬ʵ��*/


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
    cout << "������" << L.length << endl;

    //ɾ��
    int e = -1;
    if (ListDelete(L, 3, e)) {
        cout << "ɾ������" << e << endl;
    }
    else {
        cout << "λ�򲻺Ϸ�" << endl;
    }
    cout << "ɾ���󳤶���" << L.length << endl;

    //����
    ListInsert(L, 3, 10);
    for (int i = 0; i < L.length; i++) {//������ i<MaxSize ��ֻҪ����������е����ݣ����ݸ��������鳤��
        printf("data[%d]=%d\n", i, L.data[i]);
    }
    cout << "����󳤶���" << L.length << endl;

    return 0;

}