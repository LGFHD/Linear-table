#include<iostream>
using namespace std;
//#include<stdio.h>
//#include <stdlib.h>

typedef int ElemType;
//typedef int* zhengshuzhizhen;

typedef struct LNode { //���� ���������㡱 ����
	ElemType data;    //������ÿ�������һ������Ԫ��
	struct LNode* next;//ָ����ָ��ָ����һ�����
}LNode, *LinkList;
 
//����������LinkList  �� LNode* �ȼۣ�ǰ��ǿ�����ǵ���������ǿ������һ����㣩
LinkList List_HeadInsert(LinkList& L);
LNode* GetElem(LinkList L, int i);
LNode* LocateElem(LinkList L, ElemType e);
bool ListInsert(LinkList& L, int i, ElemType e);
bool InsertNextNode(LNode* p, ElemType e);
bool ListInsert(LinkList& L, int i, ElemType e);

int main()
{
	int A = 65;
	return 0;
}


//��������

//ͷ�巨����������
LinkList List_HeadInsert(LinkList& L) {		//������������
	LNode* s; int x;
	L = (LinkList)malloc(sizeof(LNode));	//����ͷ���
	L->next=NULL;							//��ʼΪ������
	cin >> x;								//�������ֵ
	while (x != 9999) {						//����9999�������
		s = (LNode*)malloc(sizeof(LNode));  //�����½��
		s->data = x;
		s->next = L->next;
		L->next = s;
		cin >> x;							//���½�������У�LΪͷָ��
	}
	return L;
}
//��ʼ��������(��ͷ���)
/*
bool InitList(LinkList& L) {//��û�����ɽ��
	L = NULL;								//��ʼ������ֹ������
	return true;
}
//�ж������Ƿ�Ϊ��
bool Empty(LinkList L) {
	return(L==NULL);
 }

*/

//��ʼ������ͷ��㣩
bool InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));		//����ͷ���
	if (L == NULL) {
		return false;						//�ڴ治�㣬����ʧ��
	}
	L->next = NULL;							//ͷ���֮����ʱû�н��							
	return true;
}

//�п�
bool Empty(LinkList L) {
	if (L->next == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//�ڵ� i ��λ�ò���Ԫ�� e
bool ListInsert(LinkList& L, int i,ElemType e) {
	if (i < 1) {	//�����λ�򲻺Ϸ�
		return false;	
	}
	LNode* p;	//ָ��pָ��ǰɨ�赽�Ľ��
	int j = 0;	//j ��¼��ǰ p ָ��ĵڼ������
	p = L;		//��ָ���������Ǳ�ʾ��ַ�����ݣ�Ҳ����ָ���Լ���ָ�򡱵ĵط�����L����p��
	              //L���ָ��ͷ��㣬����ʹ p Ҳָ��ͷ��㣬ͷ����ǵ�0����㣨�������ݣ�
	while (p != NULL && j < i - 1) {	//ѭ���ҵ��� i-1 �����
		p = p->next;
		j++;
	}
	if (p == NULL) {
		return false;
	}
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool ListInsert(LinkList& L, int i, ElemType e) {
	if (i < 1) {	//�����λ�򲻺Ϸ�						
		return false;
	}
	//LNode* s = (LNode*)malloc(sizeof(LNode));��һ�в���Ҫ
	LNode* p;	//ָ��pָ��ǰɨ�赽�Ľ��
	int j = 0;
	p = L;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	return InsertNextNode(p, e);
}
//
LNode* GetElem(LinkList L, int i) {
	if (i < 1) {
		return NULL;
	}
	int j = 1;
	LNode* p = L->next;
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	return p;
}

LNode* LocateElem(LinkList L, ElemType e) {
	LNode* p = L->next;
	while (p != NULL && p->data == e) {
		p = p->next;
	}
	return p;
}


//�� p ���֮�����Ԫ�� e
bool InsertNextNode(LNode* p, ElemType e) {
	if (p == NULL) {
		return false;
	}
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) { 
		return false; 
	}
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}



//�� p ���֮ǰ����Ԫ�� e
bool InsertPriorNode_e( LNode* p, ElemType e) {
	if (p == NULL) {
		return false;
	}
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) {
		return false;
	}
	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e;
}

//�� p ���֮ǰ������ s 
bool InsertPriorNode_s(LNode* p, LNode* s) {
	if (p == NULL || s == NULL) {
		return false;
	}
	s->next = p->next;
	p->next = s;
	ElemType temp = p->data;
	p->data == s->data;
	s->data = temp;
	return true;
}
	
bool ListDelete(LinkList& L, int i,ElemType &e) {
	if (i < 1) {
		return false;
	}
	int j = 0;
	LNode* p;
	p = L;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL) {
		return false;
	}
	if (p->next == NULL) {
		return false;
	}
	LNode* q = p->next;
	e = q->data;
	p->next = p->next->next;
	free(q);
	return true;
}

bool DeleteNode(LNode* p) {
	if (p == NULL) {
		return false;
	}
	LNode* q = p->next;
	p->data = p->next->data;
	p->next = q->next;
	/*�Ƿ���Խ�����������Ϊ��������	
	p->data = p->next->data;
	p->next=p->next->next;
	*/
}