#include<iostream>
using namespace std;

typedef int ElemType;

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLinkList;

int main() {
	return 0;
}

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
//
bool InsertNextNode(DNode* p, ElemType e) {

}