#pragma once
#ifndef chain_
#define chain_
#include<iostream>
#include"chainNode.h"
using namespace std;
template<class T>
class chain {
public:
	chain(int initialCapacity = 10);//构造方法
	chain(const chain<T>&);//复制构造方法
	~chain();//析构方法

	//成员方法
	bool empty() const { return listSize == 0; }//是否为空
	int size() const { return listSize; }//返回链表长度
	int indexOf(const T& theElement) const;//查找等于theElement的元素下标，若无则返回-1
	void erase(const T& theElement);//删除等于theElement的节点
	void insert(const T& theElement);//插入
	void output(ostream& out) const;//将链表插入输出流
	void input(istream& in);//将输入流插入链表
	void merge(chain<T> &a, chain<T> &b);//合并
	void inverse();//链表反序输出


	//迭代器
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(NULL); }
	class iterator
	{
	public:
		//迭代器所需typedef语句
		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator(chainNode<T>* theNode = NULL) {
			node = theNode;
		}
		//解引用操作符
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		iterator& operator++()   //前加
		{
			node = node->next; return *this;
		}
		iterator operator++(int) //后加
		{
			iterator old = *this;
			node = node->next;
			return old;
		}
		//相等与不等
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}
	protected:
		chainNode<T>* node;
	};
protected:
	void checkIndex(int theIndex) const;//检查下标是否合法
	chainNode<T>* firstNode;  //头节点
	int listSize;             //链表长度
};

template<class T>
chain<T>::chain(int initialCapacity)
{//构造方法，链表无需对长度设定初始值
	if (initialCapacity < 1)
	{
		throw "Initial capacity must be > 0";
	}
	firstNode = NULL;
	listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{//复制构造方法
	listSize = theList.listSize;
	if (listSize == 0)
	{//当链表为空时
		firstNode = NULL;
		return;
	}
	//复制非空链表
	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	// current last node in *this
	while (sourceNode != NULL) {
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL; // end the chain
}

template<class T>
chain<T>::~chain()
{// 析构方法
	while (firstNode != NULL)
	{// 不断删除头节点
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
void chain<T>::checkIndex(int theIndex) const
{//检查下标是否合法
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}

template<class T>
int chain<T>::indexOf(const T& theElement) const {//搜索元素
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while (currentNode != NULL &&currentNode->element != theElement) {//从链表头节点不断遍历，每次累加计数器，当元素符合时，输出计数器
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode == NULL)
		return -1;//因为链表下标从0开始，因此若不存在输出-1
	else
		return index;
}
template<class T>
void chain<T>::erase(const T& theElement) {//删除指定元素
	if (listSize == 0)
		return;
	chainNode<T> *p = firstNode, *pre = NULL;
	for (int i = 0; i < listSize; i++) {//从链表头节点不断遍历，当元素符合时，将该节点上个节点指向该节点的下一节点
		if (p->element == theElement) {
			if (p == firstNode) {
				p = p->next;
				firstNode = firstNode->next;
				listSize--;
			}
			else {
				pre->next = p->next;
				chainNode<T>* deleteNode = p;
				p = p->next;
				delete deleteNode;
				listSize--;
			}
		}
		else {
			pre = p;
			p = p->next;
		}
	}
}

template<class T>
void chain<T>::insert(const T& theElement) {//表首插入元素，每次创建新节点指向头节点
	firstNode = new chainNode<T>(theElement, firstNode);
	listSize++;
}


template<class T>
void chain<T>::inverse() {//链表反序输出
	chain<T> temp;
	for (iterator i = begin(); i != end(); i++)//用遍历器创建一个反向链表，然后输出
		temp.insert(*i);
	cout << temp << endl;
}
template<class T>
void chain<T>::merge(chain<T> &a, chain<T> &b) {
	if (a.empty() && b.empty())
		return;
	chainNode<T> *p = NULL;
	iterator i = a.begin(), j = b.begin();//声明两个链表的迭代器
	while (i != a.end() && j != b.end()) {//先将两个链表的元素不断合并，直到某个节点元素全部插入
		if (*i < *j) {
			if (listSize == 0) {
				firstNode = new chainNode<T>(*i);
				p = firstNode;
			}
			else {
				p->next = new chainNode<T>(*i);
				p = p->next;
			}
			i++;
			listSize++;
		}
		else {
			if (listSize == 0) {
				firstNode = new chainNode<T>(*i);
				p = firstNode;
			}
			else {
				p->next = new chainNode<T>(*j);
				p = p->next;
			}
			j++;
			listSize++;
		}
	}
	while (i != a.end()) {//将剩余元素插入
		p->next = new chainNode<T>(*i);
		p = p->next;
		i++;
		listSize++;
	}
	while (j != b.end()) {
		p->next = new chainNode<T>(*j);
		p = p->next;
		j++;
		listSize++;
	}
}

template<class T>
void chain<T>::output(ostream& out) const
{//重载输出运算符，使链表可以直接输出
	for (chainNode<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
		out << currentNode->element << " ";
}
template <class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}
template<class T>
void chain<T>::input(istream& in)
{// 输入
	T a;
	char c;
	in >> a;
	firstNode = new chainNode<T>(a, NULL);
	chainNode<T> *p = firstNode;
	while ((c = getchar()) != '\n') {
		in >> a;
		p->next = new chainNode<T>(a, NULL);
		p = p->next;
	}
}
template <class T>
istream& operator>>(istream& in, chain<T>& x)
{//重载输入运算符，使链表可以直接用cin创建
	x.input(in);
	return in;
}
#endif // !chain_
