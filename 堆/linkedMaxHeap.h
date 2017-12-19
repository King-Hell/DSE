
#ifndef linkedMaxHeap_
#define linkedMaxHeap_

#include "maxPriorityQueue.h"
#include "myExceptions.h"
#include <sstream>
#include <algorithm>
#include"heapNode.h"
#include<cmath>
#include"arrayQueue.h"

using namespace std;

template<class T>
class linkedMaxHeap : public maxPriorityQueue<T>
{
public:
	linkedMaxHeap() { root = NULL; heapSize = 0; }//���췽��
	~linkedMaxHeap() { erase(); }//��������
	bool empty() const { return heapSize == 0; }
	int size() const
	{
		return heapSize;
	}
	const T& top()
	{//�������Ԫ��
		if (heapSize == 0)
			throw queueEmpty();
		return root->element;
	}
	void pop();//ɾ��
	void push(const T&);//����
	void initialize(T *, int);//��ʼ��
	void deactivateArray()
	{
		heap = NULL; arrayLength = heapSize = 0;
	}
	void input(istream& in);//����������������
	void output() { levelOrder(output); cout << endl; }
	void levelOrder(void(*theVisit)(heapNode<T> *));
	void postOrder(void(*theVisit)(heapNode<T>*)) { visit = theVisit; postOrder(root); }
	void erase()
	{
		postOrder(dispose);
		root = NULL;
		heapSize = 0;
	}
private:
	int heapSize;       // �ڵ���
	heapNode<T> *root,//���ڵ�
		*last;//���ڵ�
	static void output(heapNode<T> *t) {
		cout << t->element << ' ';
	}
	static void postOrder(heapNode<T> *t);
	static void(*visit)(heapNode<T>*);
	static void dispose(heapNode<T> *t) { delete t; }
	heapNode<T>* getLast();
};
void(*linkedMaxHeap<int>::visit)(heapNode<int>*);
template<class T>
void linkedMaxHeap<T>::push(const T& theElement)
{// ���������Ԫ��
	//�÷�������Ҫ˼��Ϊ��������һ����ȫ�������ṹ����˸��ݽڵ�������Ψһȷ��һ���ѣ��̶����Լ������һ���ڵ�����λ��
	heapNode<T> *t = new heapNode<T>(theElement), *p = root;//ָ��tΪҪ����Ľڵ㣬p���ڱ�����
	if (root == NULL) {//����Ϊ��ʱ���⴦��
		root = t;
		heapSize++;
		last = root;
		return;
	}
	int level = (int)(log(heapSize + 1) / log(2) + 1);//levelΪҪ����ڵ����ڵĲ�Σ�����߲�
	int count = (int)(heapSize - pow(2, level - 1) + 2);//countΪ��߲��ڼ����½ڵ��Ԫ�صĸ���
	//��߲�������2^(k-1)��kΪ�������ڵ�
	//ÿ��ѭ�����м�ڵ����Ƚϣ���С�ڵ���������������������ұ���
	int right = (int)pow(2, level - 1);
	int left = 1;
	int mid = (left + right) / 2;
	for (int i = 1; i < level - 1; i++) {
		if (count <= mid) {
			p = p->leftChild;
			right = mid;
		}
		else {
			p = p->rightChild;
			left = mid;
		}
		mid = (left + right) / 2;
	}
	if (count % 2 == 0)//��ʱ��ȷ��Ҫ����ڵ�ĸ��ڵ㣬Ȼ���жϸýڵ������ӻ����Һ���
		p->rightChild = t;//���Һ���
	else
		p->leftChild = t;//������
	t->parent = p;
	last = t;//�����ڵ���Ϊt
	//Ȼ����Ԫ�صĴ�С�Ƿ񹹳ɴ���ѣ���Ҷ�ڵ���������
	while (t != root&&t->element > t->parent->element) {//���ýڵ�Ԫ�ش��ڸ��ڵ�Ԫ�أ��򽻻����ڵ�Ԫ��
		swap(t->element, t->parent->element);
		t = t->parent;
	}
	heapSize++;//���ڵ�������һ
}

template<class T>
void linkedMaxHeap<T>::pop()
{//ɾ�����ڵ�
	if (heapSize == 1) {//��ɾ�����ڵ����⴦��
		delete root;//�ͷſռ�
		root = NULL;
		heapSize = 0;
		last = NULL;
		return;
	}
	heapNode<T> *p = root;//pΪ������ָ��
	root->element = last->element;//�Ƚ����ڵ�Ԫ����Ϊ���һ���ڵ�Ԫ��
	if (last->parent->rightChild == NULL) {//�ٽ����һ���ڵ�ɾ��
		last->parent->leftChild = NULL;
		delete last;
	}
	else {
		last->parent->rightChild = NULL;
		delete last;
	}
	heapSize--;//�ڵ�������һ
	last = getLast();//�÷�������ȷ���µ����ڵ�
	//Ȼ���Ǵ�ʱ�Ƿ��Ǵ����
	while (p->rightChild != NULL && (p->element < p->leftChild->element || p->element < p->rightChild->element)) {
		//������ڵ�Ԫ�ش����ӽڵ�Ԫ�أ����ӽڵ��д���Ǹ�����
		if (p->leftChild->element > p->rightChild->element) {
			swap(p->element, p->leftChild->element);
			p = p->leftChild;
		}
		else {
			swap(p->element, p->rightChild->element);
			p = p->rightChild;
		}
	}
	if (p->leftChild != NULL&&p->element < p->leftChild->element) {
		swap(p->element, p->leftChild->element);
	}
}
template<class T>
heapNode<T>* linkedMaxHeap<T>::getLast() {
	//�������¼���last�ڵ㣬����뷽���еĲ���λ�ô�����ͬ
	heapNode<T> *p = root;
	int level = (int)(log(heapSize) / log(2) + 1);//�����ڵ�Ĳ��
	int count = (int)(heapSize - pow(2, level - 1) + 1);//����߲�Ľڵ����
	int right = (int)pow(2, level - 1);
	int left = 1;
	int mid = (left + right) / 2;
	for (int i = 1; i < level - 1; i++) {//��ѭ������ȷ��β�ڵ�λ�ã�ÿ��ѭ��ȷ��Ӧ�����ĸ����������
		if (count <= mid) {
			p = p->leftChild;
			right = mid;
		}
		else {
			p = p->rightChild;
			left = mid;
		}
		mid = (left + right) / 2;
	}
	if (count % 2 == 0)//�������ڵ�λ��
		return p->rightChild;
	else
		return p->leftChild;
}
template<class T>
void linkedMaxHeap<T>::initialize(T *theHeap, int theSize)
{
	for (int i = 1; i < theSize; i++)
		push(theHeap[i]);
}

template <class T>
void linkedMaxHeap<T>::levelOrder(void(*theVisit)(heapNode<T> *))
{// ��α���
	arrayQueue<heapNode<T>*> q;
	heapNode<T> *t = root;
	while (t != NULL)
	{
		theVisit(t);

		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);

		try { t = q.front(); }
		catch (queueEmpty) { return; }
		q.pop();
	}
}
template<class T>
void linkedMaxHeap<T>::postOrder(heapNode<T> *t)
{// �������
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedMaxHeap<T>::visit(t);
	}
}
template<class T>
void linkedMaxHeap<T>::input(istream& in)
{// ����
	T a;
	char c;
	in >> a;
	push(a);
	while ((c = getchar()) != '\n') {
		in >> a;
		push(a);
	}
}
template<class T>
ostream& operator<<(ostream& out, linkedMaxHeap<T>& x) {
	x.output();
	return out;
}
template<class T>
istream& operator>>(istream& in, linkedMaxHeap<T>& x)
{//���������������ʹ�������ֱ����cin����
	x.input(in);
	return in;
}
#endif
