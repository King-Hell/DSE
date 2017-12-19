
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
	linkedMaxHeap() { root = NULL; heapSize = 0; }//构造方法
	~linkedMaxHeap() { erase(); }//析构方法
	bool empty() const { return heapSize == 0; }
	int size() const
	{
		return heapSize;
	}
	const T& top()
	{//返回最大元素
		if (heapSize == 0)
			throw queueEmpty();
		return root->element;
	}
	void pop();//删除
	void push(const T&);//插入
	void initialize(T *, int);//初始化
	void deactivateArray()
	{
		heap = NULL; arrayLength = heapSize = 0;
	}
	void input(istream& in);//将输入流插入链表
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
	int heapSize;       // 节点数
	heapNode<T> *root,//根节点
		*last;//最后节点
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
{// 向堆中增加元素
	//该方法的主要思想为：堆总是一个完全二叉树结构，因此根据节点数可以唯一确定一个堆，继而可以计算出下一个节点插入的位置
	heapNode<T> *t = new heapNode<T>(theElement), *p = root;//指针t为要插入的节点，p用于遍历堆
	if (root == NULL) {//当根为空时特殊处理
		root = t;
		heapSize++;
		last = root;
		return;
	}
	int level = (int)(log(heapSize + 1) / log(2) + 1);//level为要插入节点所在的层次，即最高层
	int count = (int)(heapSize - pow(2, level - 1) + 2);//count为最高层在加入新节点后元素的个数
	//最高层最多插入2^(k-1)，k为层数个节点
	//每次循环与中间节点数比较，若小于等于则向左遍历，大于向右遍历
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
	if (count % 2 == 0)//此时已确定要插入节点的父节点，然后判断该节点是左孩子还是右孩子
		p->rightChild = t;//是右孩子
	else
		p->leftChild = t;//是左孩子
	t->parent = p;
	last = t;//将最后节点置为t
	//然后考虑元素的大小是否构成大根堆，从叶节点向上起泡
	while (t != root&&t->element > t->parent->element) {//若该节点元素大于父节点元素，则交换两节点元素
		swap(t->element, t->parent->element);
		t = t->parent;
	}
	heapSize++;//最后节点总数加一
}

template<class T>
void linkedMaxHeap<T>::pop()
{//删除最大节点
	if (heapSize == 1) {//若删除根节点特殊处理
		delete root;//释放空间
		root = NULL;
		heapSize = 0;
		last = NULL;
		return;
	}
	heapNode<T> *p = root;//p为遍历用指针
	root->element = last->element;//先将根节点元素置为最后一个节点元素
	if (last->parent->rightChild == NULL) {//再将最后一个节点删除
		last->parent->leftChild = NULL;
		delete last;
	}
	else {
		last->parent->rightChild = NULL;
		delete last;
	}
	heapSize--;//节点总数减一
	last = getLast();//该方法用于确定新的最后节点
	//然后考虑此时是否是大根堆
	while (p->rightChild != NULL && (p->element < p->leftChild->element || p->element < p->rightChild->element)) {
		//如果根节点元素大于子节点元素，则将子节点中大的那个交换
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
	//用于重新计算last节点，与插入方法中的查找位置大致相同
	heapNode<T> *p = root;
	int level = (int)(log(heapSize) / log(2) + 1);//求最后节点的层次
	int count = (int)(heapSize - pow(2, level - 1) + 1);//求最高层的节点个数
	int right = (int)pow(2, level - 1);
	int left = 1;
	int mid = (left + right) / 2;
	for (int i = 1; i < level - 1; i++) {//该循环用于确定尾节点位置，每次循环确定应该向哪个方向遍历树
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
	if (count % 2 == 0)//返回最后节点位置
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
{// 层次遍历
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
{// 后序遍历
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedMaxHeap<T>::visit(t);
	}
}
template<class T>
void linkedMaxHeap<T>::input(istream& in)
{// 输入
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
{//重载输入运算符，使链表可以直接用cin创建
	x.input(in);
	return in;
}
#endif
