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

//1.初始化双链表节点
bool InitList(DLinkList& L) {
	L = new DNode;
	if (!L) {
		cout << "申请节点失败！" << endl;
		return false;
	}
	else {
		L->next = NULL;//初始化后继指针
		L->prior = NULL;//初始化前驱指针
		cout << "申请节点成功！" << endl;
		return true;
	}
}
//
bool InsertNextNode(DNode* p, ElemType e) {

}