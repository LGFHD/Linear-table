#include<iostream>
using namespace std;

typedef int ElemType;

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLinkList;

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
//2.打印双链表
bool PrintList(DLinkList& L){
	if (L->next == NULL) {//注意是判断L->next而不是L
		cout << "链表为空" << endl;
		return false;
	}
	DNode* p = L->next;//要新建一个指针p来输出数据
	while (p) {
		cout << p->data << endl;
		p = p->next;
	}
	return true;
}
//3.获取有效长度
int ListLength(DLinkList& L) {
	DNode* p = L->next;//申请一个新节点
	int length = 0;//该变量用来保存长度
	while (p) {//p不为空时执行,若p为空，则length就为初始值0
		length++;//长度加1
		p = p->next;//节点向后移动
	}
	cout << endl;//只是为了换行
	return length;
}
//4.头插法建立双链表
bool ListHeadInsert(DLinkList& L) {
	ElemType x;
	DNode* p;
	cin >> x;
	while (x != 9999) {
		p = new DNode;
		p->data = x;
		p->next = L->next;
		if (L->next != NULL) {
			//如果插入的是第一个结点，那么L->next就是NULL,此时无法将NULL的prior指针指向新插入的结点
			L->next->prior = p;
		}
		p->prior = L;
		L->next = p;
		cin >> x;
	}
	PrintList(L);
	return true;
}
//5.尾插法建立双链表
DLinkList ListTailInsert(DLinkList& L) {
	ElemType x;
	DNode* p, *r = L;//尾指针r和接收数据的指针p
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
//按值查找与按位查找与单链表相同
// 
//6.在p结点后插入结点s
bool InsertNextNode_s(DNode* p, DNode* s) {
	if (p == NULL) {
		cout << "结点p不存在" << endl;
		return false;
	}
	s->next = p->next;//1
	p->next->prior = s;//2
	s->prior = p;//3
	p->next = s;//4			//1、2两步必须在4之前
	return true;
}
//7.删除p的后继结点q
bool DeleteNode_b(DNode* p) {
	if (p == NULL) {
		cout << "结点p不存在" << endl;
		return false;
	}
	DNode* q = p->next;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return true;
}
//删除p的前驱结点q
bool DeleteNode_f(DNode* p) {
	DNode* r=new DNode;
	//这里还要考虑第一和二个结点，这两个结点用此代码不行；
	p->prior->prior = r;//找到p的前驱的前驱r,调用删除后继结点的函数，删除r的后继结点q
	bool res=DeleteNode_b(r);
	return res;
}


int main() {
	DLinkList L;//定义一个双链表L
	InitList(L);//为链表L初始化
	ListTailInsert(L);//使用头插法创建双链表
	return 0;
}