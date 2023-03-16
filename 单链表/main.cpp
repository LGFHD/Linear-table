#include<iostream>
using namespace std;

typedef int ElemType;
//typedef int* zhengshuzhizhen;

typedef struct LNode { //���� ���������㡱 ����
	ElemType data;    //������ÿ�������һ������Ԫ��
	struct LNode* next;//ָ����ָ��ָ����һ�����
}LNode, * LinkList;

//����������LinkList  �� LNode* �ȼۣ�ǰ��ǿ�����ǵ���������ǿ������һ����㣩
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


//��������
//ͷ�巨����������
LinkList List_HeadInsert(LinkList& L) {		//������������
	LNode* s; int x;
	L = new LNode;
//	L = (LinkList)malloc(sizeof(LNode));	//����ͷ���
	L->next=NULL;							//��ʼΪ������
	cin >> x;								//�������ֵ
	while (x != 9999) {						//����9999�������
		s = new LNode;
		//s = (LNode*)malloc(sizeof(LNode));  //�����½��
		s->data = x;
		s->next = L->next;
		L->next = s;
		cin >> x;							//���½�������У�LΪͷָ��
	}
	return L;
}
//β�巨����������
LinkList List_TailInsert(LinkList& L) {//������������
	int x;							   //��Ԫ������Ϊ����
	L = new LNode;//Ϊͷָ������洢�ռ�
	LNode* s, * r = L;//rΪ��βָ�룬ʼ��ָ���β��sΪ�������ݵ�ָ��
	cin >> x;
	while (x != 9999) {
		s = new LNode;//�����¿ռ�洢������
		s->data = x;
		r->next = s;
	// r ʼ��ָ���β����ʼ״ָ̬��ͷ��㣩�����µĽ�����ʱ���½��Ҫ��Ϊ���һ��ָ�룬��r��nextָ���½�㣬ʹ�½���Ϊ���һ��ָ��
		r = s;//����ٽ�rָ���β���
		cin >> x;
	}
	r->next = NULL;//β���ָ���ÿ�
	return L;
}
//������(��ͷ��㣬����ɾ����һ��Ԫ��Ҫ����ͷָ��)
/*
 //��ʼ��
bool InitList(LinkList& L) {//��û�����ɽ��
	L = NULL;								//��ʼ������ֹ������
	return true;
}
//�ж������Ƿ�Ϊ��
bool Empty(LinkList L) {
	return(L==NULL);
 }

 //�ڵ� i ��λ�ò���Ԫ�� e���ҵ��� i-1 ��㣬����������룩
bool ListInsert(LinkList& L, int i, ElemType e) {
	if (i < 1) {
		return false;
	}
	if (i == 1){	//�����һ�����ʱ�Ĳ�����������㲻ͬ
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;	//��������
		s->next = L;	//L ָ�����������������ʾ��ַ�ģ�Ҳ���� L ָ��ָ��ĵ�ַ��ָ���һ����㣩��
						//��ͷָ�� L �����ݸ��� s ��ָ���򣬴�ʱָ�� s ָ���һ�����
		L = s;			//��ָ�� s ���ĵ�ַ������ͷָ�� L ����ʱͷָ�� L ָ���²���Ľ�㣨��һ����㣩 s
		return true;
	}
	LNode* p;
	int j = 1;
	p = L;				// p ָ���һ����㣨ע�ⲻ��ͷ��㣩
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

//ɾ����һ����㣬����ͷ��������£���ô�죿


*/

//************************************************** ��ͷ���
// һ��ͷ�����ĸ��洢���ݵĽ�㣬��ô��������Ϊ 5

//1.��ʼ��
bool InitList(LinkList& L) {
	L = new LNode;
	//L = (LNode*)malloc(sizeof(LNode));		//����ͷ���
	if (L == NULL) {
		return false;						//�ڴ治�㣬����ʧ��
	}
	L->next = NULL;							//ͷ���֮����ʱû�н��							
	return true;
}

//2.�п�
bool Empty(LinkList L) {
	if (L->next == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//3.��λ����
LNode* GetElem(LinkList L, int i) {
	if (i < 0) {
		return NULL;
	}
	int j = 0;	//��ǰ  p ָ����ǵڼ������
	LNode* p;	//ָ��ǰɨ�赽�Ľ��
	p = L;		//ָ��ͷ��㣬ͷ�ڵ��ǵ�0����㣬��������
	while (p != NULL && j < i) {	//ѭ���ҵ��� i �����
		p = p->next;
		j++;
	}
	return p;
}

//4.��ֵ���ң�����ж������ṹ���Ƿ���ȣ�
LNode* LocateElem(LinkList L, ElemType e) {
	LNode* p = L->next;
	//�ӵ�һ����㿪ʼ����������Ϊ e �Ľ��
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	return p;	//�ҵ��󷵻�ָ�� p �����򷵻�NULL
}

//5.���
int Length(LinkList L) {
	int len = 0;
	LNode* p = L;
	while (p->next != NULL) {
		p = p->next;
		len++;
	}
	return len;
}

//�ڵ� i ��λ�ò���Ԫ�� e(δ���ú���)���ҵ��� i-1 ��㣬����������룩
/*
bool ListInsert(LinkList& L, int i,ElemType e) {
	if (i < 1) {	//�����λ�򲻺Ϸ�
		return false;
	}
		//*************************��һ���ִ��룺�ҵ��� i-1 �����****************
		LNode* p;	//ָ��pָ��ǰɨ�赽�Ľ��
		int j = 0;	//j ��¼��ǰ p ָ��ĵڼ������
		p = L;		//��ָ���������Ǳ�ʾ��ַ�����ݣ�Ҳ����ָ���Լ���ָ�򡱵ĵط�����L����p��
		//L���ָ��ͷ��㣬����ʹ p Ҳָ��ͷ��㣬ͷ����ǵ�0����㣨�������ݣ�
		while (p != NULL && j < i - 1) {	//ѭ���ҵ��� i-1 �����
			//�ж�ָ�� p �Ƿ�Ϊ�գ������ж�ָ�� p ָ��Ľ���Ƿ�Ϊ��
			p = p->next;
			j++;
		}
		//******************��һ���ִ��룺�ڵ� i-1 ����������½��*****************
		if (p == NULL) {		// i ֵ���Ϸ���iֵ����������ʱ������ i=6 ,��ʱ p Ϊ NULL ��
			return false;
		}
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;
		s->next = p->next;
		p->next = s;	//����� s ���ӵ� p ֮��

	return true;	//����ɹ�
}
*/

//�ڵ� i ��λ�ò���Ԫ�� e�����ú���������ࣩ���ҵ��� i-1 ��㣬����������룩
bool ListInsert(LinkList& L, int i, ElemType e) {
	if (i < 1) {	//�����λ�򲻺Ϸ�						
		return false;
	}
	LNode* p = GetElem(L, i - 1);	//���ú����ҵ��� i-1 ����㣬��� i ֵ���Ϸ�����᷵��NULL
	return InsertNextNode(p, e);	//�� i ֵ���Ϸ������뵽InsertNextNode�е� p ����NULL
}

//�� p ���֮�����Ԫ�� e
bool InsertNextNode(LNode* p, ElemType e) {
	if (p == NULL) {		//�����п����б�Ҫ��!
		//���磺��ListInsert�����У�������� i ֵ���Ϸ���GetElem�����᷵��NULL����ʱInsertNextNode�ͻ��յ�ֵΪNULL�� p 
		return false;
	}
	LNode *s = new LNode;
	//LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) {	// �ڴ����ʧ��
		return false;
	}
	s->data = e;	//���s��������e
	s->next = p->next;
	p->next = s;
	return true;
}

//�� p ���֮ǰ����Ԫ�� e
bool InsertPriorNode_e(LNode* p, ElemType e) {
	if (p == NULL) {
		return false;
	}
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL) {			//�ڴ����ʧ��
		return false;
	}
	s->next = p->next;
	p->next = s;		//�Ƚ��½�� s ����  p ֮�� 
	s->data = p->data;	//�� p ��Ԫ�ظ��Ƶ� s ����� 
	p->data = e;	//��Ҫ��������� e ���� p �е�����
}

//�� p ���֮ǰ������ s 
bool InsertPriorNode_s(LNode* p, LNode* s) {
	if (p == NULL || s == NULL) {
		return false;
	}
	s->next = p->next;
	p->next = s;	//	s ���� p ֮��
	ElemType temp = p->data;	//��ʼ��������
	p->data == s->data;
	s->data = temp;
	return true;
}

//ɾ���� i ����㣬������ɾ����ֵ���ҵ��� i-1 ����㣬����ָ��� i+1 ����㣩
bool ListDelete(LinkList& L, int i, ElemType& e) {
	if (i < 1) {
		return false;
	}
	/*int j = 0;	//�ҵ���i-1�����
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
	if (p->next == NULL) {	//�� i-1 �����֮�������������
		return false;
	}
	LNode* q = p->next;		//�� q ָ��ɾ���Ľ��
	e = q->data;			//�� e ����ɾ��Ԫ�ص�ֵ
	p->next = p->next->next;//�Ͽ� q ���
	free(q);
	return true;
}

//ɾ��ָ����� p
bool DeleteNode(LNode* p) {
	if (p == NULL) {
		return false;
	}
	LNode* q = p->next;		//�� q ָ�� p �ĺ�̽�� (��� p �����һ����㣬ֻ�ܴӵ�һ����㿪ʼ����Ѱ�� p ��ǰ��)
	p->data = p->next->data;// p �ĺ�̽�� q �����ݸ��Ƶ� p �����,p �� q ������һ�£�p ��Ҫɾ���ģ�p ������ֱ�Ӹ��Ǿͺ��ˣ�
	p->next = q->next;		//�� q �����жϿ�����ʱ q �е������Ѿ����Ƶ� p �У���ʱֱ��ɾ�� q �Ϳɣ�
	/*�Ƿ���Խ�����������Ϊ��������
	p->data = p->next->data;
	p->next=p->next->next;
	*/
	free(q);
	return true;
}