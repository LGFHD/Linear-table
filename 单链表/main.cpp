#include<iostream>
using namespace std;
//#include<stdio.h>
//#include <stdlib.h>

typedef int ElemType;
//typedef int* zhengshuzhizhen;

typedef struct LNode { //定义 “单链表结点” 类型
	ElemType data;    //数据域：每个结点存放一个数据元素
	struct LNode* next;//指针域：指针指向下一个结点
}LNode, *LinkList;
 
//函数声明（LinkList  与 LNode* 等价，前者强调这是单链表，后者强调这是一个结点）
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


//函数定义

//头插法建立单链表
LinkList List_HeadInsert(LinkList& L) {		//逆向建立单链表
	LNode* s; int x;
	L = (LinkList)malloc(sizeof(LNode));	//创建头结点
	L->next=NULL;							//初始为空链表
	cin >> x;								//输入结点的值
	while (x != 9999) {						//输入9999代表结束
		s = (LNode*)malloc(sizeof(LNode));  //创建新结点
		s->data = x;
		s->next = L->next;
		L->next = s;
		cin >> x;							//将新结点插入表中，L为头指针
	}
	return L;
}
//初始化单链表(无头结点)
/*
bool InitList(LinkList& L) {//并没有生成结点
	L = NULL;								//初始化，防止脏数据
	return true;
}
//判断链表是否为空
bool Empty(LinkList L) {
	return(L==NULL);
 }

*/

//初始化（有头结点）
bool InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));		//分配头结点
	if (L == NULL) {
		return false;						//内存不足，分配失败
	}
	L->next = NULL;							//头结点之后暂时没有结点							
	return true;
}

//判空
bool Empty(LinkList L) {
	if (L->next == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//在第 i 个位置插入元素 e
bool ListInsert(LinkList& L, int i,ElemType e) {
	if (i < 1) {	//输入的位序不合法
		return false;	
	}
	LNode* p;	//指针p指向当前扫描到的结点
	int j = 0;	//j 记录当前 p 指向的第几个结点
	p = L;		//（指针里面存的是表示地址的数据，也就是指针自己“指向”的地方，将L赋给p）
	              //L最初指向头结点，这里使 p 也指向头结点，头结点是第0个结点（不存数据）
	while (p != NULL && j < i - 1) {	//循环找到第 i-1 个结点
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
	if (i < 1) {	//输入的位序不合法						
		return false;
	}
	//LNode* s = (LNode*)malloc(sizeof(LNode));这一行不需要
	LNode* p;	//指针p指向当前扫描到的结点
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


//在 p 结点之后插入元素 e
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



//在 p 结点之前插入元素 e
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

//在 p 结点之前插入结点 s 
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
	/*是否可以将上面三步化为下面两步	
	p->data = p->next->data;
	p->next=p->next->next;
	*/
}