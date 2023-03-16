#include<iostream>
using namespace std;

typedef int ElemType;
//typedef int* zhengshuzhizhen;

typedef struct LNode { //定义 “单链表结点” 类型
	ElemType data;    //数据域：每个结点存放一个数据元素
	struct LNode* next;//指针域：指针指向下一个结点
}LNode, * LinkList;

//函数声明（LinkList  与 LNode* 等价，前者强调这是单链表，后者强调这是一个结点）
LinkList List_HeadInsert(LinkList& L);
LinkList List_TailInsert(LinkList& L);
LNode* GetElem(LinkList L, int i);
LNode* LocateElem(LinkList L, ElemType e);
bool ListInsert(LinkList& L, int i, ElemType e);
bool InsertNextNode(LNode* p, ElemType e);
bool ListInsert(LinkList& L, int i, ElemType e);
int Length(LinkList L);

int main()
{
	LinkList L;
	List_TailInsert(L);
	for (int i = 0; i < 10; i++) {
		cout << L->data << endl;
		L = L->next;
	}
	return 0;
}


//函数定义
//头插法建立单链表
LinkList List_HeadInsert(LinkList& L) {		//逆向建立单链表
	LNode* s; int x;
	L = new LNode;
//	L = (LinkList)malloc(sizeof(LNode));	//创建头结点
	L->next=NULL;							//初始为空链表
	cin >> x;								//输入结点的值
	while (x != 9999) {						//输入9999代表结束
		s = new LNode;
		//s = (LNode*)malloc(sizeof(LNode));  //创建新结点
		s->data = x;
		s->next = L->next;
		L->next = s;
		cin >> x;							//将新结点插入表中，L为头指针
	}
	return L;
}
//尾插法建立单链表
LinkList List_TailInsert(LinkList& L) {//正向建立单链表
	int x;							   //设元素类型为整型
	L = new LNode;//为头指针申请存储空间
	LNode* s, * r = L;//r为表尾指针，始终指向表尾；s为接受数据的指针
	cin >> x;
	while (x != 9999) {
		s = new LNode;//申请新空间存储新数据
		s->data = x;
		r->next = s;
	// r 始终指向表尾（初始状态指向头结点），有新的结点插入时，新结点要成为最后一个指针，让r的next指向新结点，使新结点成为最后一个指针
		r = s;//随后再将r指针表尾结点
		cin >> x;
	}
	r->next = NULL;//尾结点指针置空
	return L;
}
//单链表(无头结点，插入删除第一个元素要更改头指针)
/*
 //初始化
bool InitList(LinkList& L) {//并没有生成结点
	L = NULL;								//初始化，防止脏数据
	return true;
}
//判断链表是否为空
bool Empty(LinkList L) {
	return(L==NULL);
 }

 //在第 i 个位置插入元素 e（找到第 i-1 结点，在它后面插入）
bool ListInsert(LinkList& L, int i, ElemType e) {
	if (i < 1) {
		return false;
	}
	if (i == 1){	//插入第一个结点时的操作与其他结点不同
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;	//赋入数据
		s->next = L;	//L 指针里的数据是用来表示地址的，也就是 L 指针指向的地址（指向第一个结点），
						//将头指针 L 的数据赋给 s 的指针域，此时指针 s 指向第一个结点
		L = s;			//将指针 s （的地址）赋给头指针 L ，此时头指针 L 指向新插入的结点（第一个结点） s
		return true;
	}
	LNode* p;
	int j = 1;
	p = L;				// p 指向第一个结点（注意不是头结点）
	while (p != NULL && j < i - 1) {
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

//删除第一个结点，不带头结点的情况下，怎么办？


*/

//************************************************** 有头结点
// 一个头结点加四个存储数据的结点，那么该链表长度为 5

//1.初始化
bool InitList(LinkList& L) {
	L = new LNode;
	//L = (LNode*)malloc(sizeof(LNode));		//分配头结点
	if (L == NULL) {
		return false;						//内存不足，分配失败
	}
	L->next = NULL;							//头结点之后暂时没有结点							
	return true;
}

//2.判空
bool Empty(LinkList L) {
	if (L->next == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//3.按位查找
LNode* GetElem(LinkList L, int i) {
	if (i < 0) {
		return NULL;
	}
	int j = 0;	//当前  p 指向的是第几个结点
	LNode* p;	//指向当前扫描到的结点
	p = L;		//指向头结点，头节点是第0个结点，不存数据
	while (p != NULL && j < i) {	//循环找到第 i 个结点
		p = p->next;
		j++;
	}
	return p;
}

//4.按值查找（如何判断两个结构体是否相等）
LNode* LocateElem(LinkList L, ElemType e) {
	LNode* p = L->next;
	//从第一个结点开始查找数据域为 e 的结点
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	return p;	//找到后返回指针 p ，否则返回NULL
}

//5.求表长
int Length(LinkList L) {
	int len = 0;
	LNode* p = L;
	while (p->next != NULL) {
		p = p->next;
		len++;
	}
	return len;
}

//在第 i 个位置插入元素 e(未调用函数)（找到第 i-1 结点，在它后面插入）
/*
bool ListInsert(LinkList& L, int i,ElemType e) {
	if (i < 1) {	//输入的位序不合法
		return false;
	}
		//*************************这一部分代码：找到第 i-1 个结点****************
		LNode* p;	//指针p指向当前扫描到的结点
		int j = 0;	//j 记录当前 p 指向的第几个结点
		p = L;		//（指针里面存的是表示地址的数据，也就是指针自己“指向”的地方，将L赋给p）
		//L最初指向头结点，这里使 p 也指向头结点，头结点是第0个结点（不存数据）
		while (p != NULL && j < i - 1) {	//循环找到第 i-1 个结点
			//判断指针 p 是否为空，是在判断指针 p 指向的结点是否为空
			p = p->next;
			j++;
		}
		//******************这一部分代码：在第 i-1 个结点后插入新结点*****************
		if (p == NULL) {		// i 值不合法（i值超过链表长度时，例如 i=6 ,此时 p 为 NULL ）
			return false;
		}
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;
		s->next = p->next;
		p->next = s;	//将结点 s 连接到 p 之后

	return true;	//插入成功
}
*/

//在第 i 个位置插入元素 e（调用函数，更简洁）（找到第 i-1 结点，在它后面插入）
bool ListInsert(LinkList& L, int i, ElemType e) {
	if (i < 1) {	//输入的位序不合法						
		return false;
	}
	LNode* p = GetElem(L, i - 1);	//调用函数找到第 i-1 个结点，如果 i 值不合法，则会返回NULL
	return InsertNextNode(p, e);	//若 i 值不合法，输入到InsertNextNode中的 p 就是NULL
}

//在 p 结点之后插入元素 e
bool InsertNextNode(LNode* p, ElemType e) {
	if (p == NULL) {		//这里判空是有必要的!
		//例如：在ListInsert函数中，若输入的 i 值不合法，GetElem函数会返回NULL，此时InsertNextNode就会收到值为NULL的 p 
		return false;
	}
	LNode *s = new LNode;
	//LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) {	// 内存分配失败
		return false;
	}
	s->data = e;	//结点s保存数据e
	s->next = p->next;
	p->next = s;
	return true;
}

//在 p 结点之前插入元素 e
bool InsertPriorNode_e(LNode* p, ElemType e) {
	if (p == NULL) {
		return false;
	}
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) {			//内存分配失败
		return false;
	}
	s->next = p->next;
	p->next = s;		//先将新结点 s 连到  p 之后 
	s->data = p->data;	//将 p 中元素复制到 s 结点中 
	p->data = e;	//将要插入的数据 e 覆盖 p 中的数据
}

//在 p 结点之前插入结点 s 
bool InsertPriorNode_s(LNode* p, LNode* s) {
	if (p == NULL || s == NULL) {
		return false;
	}
	s->next = p->next;
	p->next = s;	//	s 连到 p 之后
	ElemType temp = p->data;	//开始交换数据
	p->data == s->data;
	s->data = temp;
	return true;
}

//删除第 i 个结点，并返回删除的值（找到第 i-1 个结点，将其指向第 i+1 个结点）
bool ListDelete(LinkList& L, int i, ElemType& e) {
	if (i < 1) {
		return false;
	}
	/*int j = 0;	//找到第i-1个结点
	LNode* p;
	p = L;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}*/
	LNode* p = GetElem(L, i - 1);
	if (p == NULL) {			
		return false;
	}
	if (p->next == NULL) {	//第 i-1 个结点之后已无其他结点
		return false;
	}
	LNode* q = p->next;		//令 q 指向被删除的结点
	e = q->data;			//用 e 返回删除元素的值
	p->next = p->next->next;//断开 q 结点
	free(q);
	return true;
}

//删除指定结点 p
bool DeleteNode(LNode* p) {
	if (p == NULL) {
		return false;
	}
	LNode* q = p->next;		//令 q 指向 p 的后继结点 (如果 p 是最后一个结点，只能从第一个结点开始依次寻找 p 的前驱)
	p->data = p->next->data;// p 的后继结点 q 的数据复制到 p 结点中,p 和 q 中数据一致（p 是要删除的，p 中数据直接覆盖就好了）
	p->next = q->next;		//将 q 结点从中断开（此时 q 中的数据已经复制到 p 中，这时直接删除 q 就可）
	/*是否可以将上面三步化为下面两步
	p->data = p->next->data;
	p->next=p->next->next;
	*/
	free(q);
	return true;
}