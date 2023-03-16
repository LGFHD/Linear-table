#include<iostream>
using namespace std;

typedef int ElemType;

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLinkList;

//1.��ʼ��˫����ڵ�
bool InitList(DLinkList& L) {
	L = new DNode;
	if (!L) {
		cout << "����ڵ�ʧ�ܣ�" << endl;
		return false;
	}
	else {
		L->next = NULL;//��ʼ�����ָ��
		L->prior = NULL;//��ʼ��ǰ��ָ��
		cout << "����ڵ�ɹ���" << endl;
		return true;
	}
}
//2.��ӡ˫����
bool PrintList(DLinkList& L){
	if (L->next == NULL) {//ע�����ж�L->next������L
		cout << "����Ϊ��" << endl;
		return false;
	}
	DNode* p = L->next;//Ҫ�½�һ��ָ��p���������
	while (p) {
		cout << p->data << endl;
		p = p->next;
	}
	return true;
}
//3.��ȡ��Ч����
int ListLength(DLinkList& L) {
	DNode* p = L->next;//����һ���½ڵ�
	int length = 0;//�ñ����������泤��
	while (p) {//p��Ϊ��ʱִ��,��pΪ�գ���length��Ϊ��ʼֵ0
		length++;//���ȼ�1
		p = p->next;//�ڵ�����ƶ�
	}
	cout << endl;//ֻ��Ϊ�˻���
	return length;
}
//4.ͷ�巨����˫����
bool ListHeadInsert(DLinkList& L) {
	ElemType x;
	DNode* p;
	cin >> x;
	while (x != 9999) {
		p = new DNode;
		p->data = x;
		p->next = L->next;
		if (L->next != NULL) {
			//���������ǵ�һ����㣬��ôL->next����NULL,��ʱ�޷���NULL��priorָ��ָ���²���Ľ��
			L->next->prior = p;
		}
		p->prior = L;
		L->next = p;
		cin >> x;
	}
	PrintList(L);
	return true;
}
//5.β�巨����˫����
DLinkList ListTailInsert(DLinkList& L) {
	ElemType x;
	DNode* p, *r = L;//βָ��r�ͽ������ݵ�ָ��p
	cin >> x;
	while (x != 9999){
		 p = new DNode;
		 p->data = x;
		 p->next = NULL;
		 p->prior = r;
		 r->next = p;
		 r = p;
		 r->next = NULL;
		 cin >> x;
	}
	PrintList(L);
	return L;
}
//��ֵ�����밴λ�����뵥������ͬ
// 
//6.��p���������s
bool InsertNextNode_s(DNode* p, DNode* s) {
	if (p == NULL) {
		cout << "���p������" << endl;
		return false;
	}
	s->next = p->next;//1
	p->next->prior = s;//2
	s->prior = p;//3
	p->next = s;//4			//1��2����������4֮ǰ
	return true;
}
//7.ɾ��p�ĺ�̽��q
bool DeleteNode_b(DNode* p) {
	if (p == NULL) {
		cout << "���p������" << endl;
		return false;
	}
	DNode* q = p->next;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return true;
}
//ɾ��p��ǰ�����q
bool DeleteNode_f(DNode* p) {
	DNode* r=new DNode;
	//���ﻹҪ���ǵ�һ�Ͷ�����㣬����������ô˴��벻�У�
	p->prior->prior = r;//�ҵ�p��ǰ����ǰ��r,����ɾ����̽��ĺ�����ɾ��r�ĺ�̽��q
	bool res=DeleteNode_b(r);
	return res;
}


int main() {
	DLinkList L;//����һ��˫����L
	InitList(L);//Ϊ����L��ʼ��
	ListTailInsert(L);//ʹ��ͷ�巨����˫����
	return 0;
}