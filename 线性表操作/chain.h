#pragma once
#ifndef chain_
#define chain_
#include<iostream>
#include"chainNode.h"
using namespace std;
template<class T>
class chain {
public:
	chain(int initialCapacity = 10);//���췽��
	chain(const chain<T>&);//���ƹ��췽��
	~chain();//��������

	//��Ա����
	bool empty() const { return listSize == 0; }//�Ƿ�Ϊ��
	int size() const { return listSize; }//����������
	int indexOf(const T& theElement) const;//���ҵ���theElement��Ԫ���±꣬�����򷵻�-1
	void erase(const T& theElement);//ɾ������theElement�Ľڵ�
	void insert(const T& theElement);//����
	void output(ostream& out) const;//��������������
	void input(istream& in);//����������������
	void merge(chain<T> &a, chain<T> &b);//�ϲ�
	void inverse();//���������


	//������
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(NULL); }
	class iterator
	{
	public:
		//����������typedef���
		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator(chainNode<T>* theNode = NULL) {
			node = theNode;
		}
		//�����ò�����
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		iterator& operator++()   //ǰ��
		{
			node = node->next; return *this;
		}
		iterator operator++(int) //���
		{
			iterator old = *this;
			node = node->next;
			return old;
		}
		//����벻��
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
	void checkIndex(int theIndex) const;//����±��Ƿ�Ϸ�
	chainNode<T>* firstNode;  //ͷ�ڵ�
	int listSize;             //������
};

template<class T>
chain<T>::chain(int initialCapacity)
{//���췽������������Գ����趨��ʼֵ
	if (initialCapacity < 1)
	{
		throw "Initial capacity must be > 0";
	}
	firstNode = NULL;
	listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{//���ƹ��췽��
	listSize = theList.listSize;
	if (listSize == 0)
	{//������Ϊ��ʱ
		firstNode = NULL;
		return;
	}
	//���Ʒǿ�����
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
{// ��������
	while (firstNode != NULL)
	{// ����ɾ��ͷ�ڵ�
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
void chain<T>::checkIndex(int theIndex) const
{//����±��Ƿ�Ϸ�
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}

template<class T>
int chain<T>::indexOf(const T& theElement) const {//����Ԫ��
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while (currentNode != NULL &&currentNode->element != theElement) {//������ͷ�ڵ㲻�ϱ�����ÿ���ۼӼ���������Ԫ�ط���ʱ�����������
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode == NULL)
		return -1;//��Ϊ�����±��0��ʼ����������������-1
	else
		return index;
}
template<class T>
void chain<T>::erase(const T& theElement) {//ɾ��ָ��Ԫ��
	if (listSize == 0)
		return;
	chainNode<T> *p = firstNode, *pre = NULL;
	for (int i = 0; i < listSize; i++) {//������ͷ�ڵ㲻�ϱ�������Ԫ�ط���ʱ�����ýڵ��ϸ��ڵ�ָ��ýڵ����һ�ڵ�
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
void chain<T>::insert(const T& theElement) {//���ײ���Ԫ�أ�ÿ�δ����½ڵ�ָ��ͷ�ڵ�
	firstNode = new chainNode<T>(theElement, firstNode);
	listSize++;
}


template<class T>
void chain<T>::inverse() {//���������
	chain<T> temp;
	for (iterator i = begin(); i != end(); i++)//�ñ���������һ����������Ȼ�����
		temp.insert(*i);
	cout << temp << endl;
}
template<class T>
void chain<T>::merge(chain<T> &a, chain<T> &b) {
	if (a.empty() && b.empty())
		return;
	chainNode<T> *p = NULL;
	iterator i = a.begin(), j = b.begin();//������������ĵ�����
	while (i != a.end() && j != b.end()) {//�Ƚ����������Ԫ�ز��Ϻϲ���ֱ��ĳ���ڵ�Ԫ��ȫ������
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
	while (i != a.end()) {//��ʣ��Ԫ�ز���
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
{//��������������ʹ�������ֱ�����
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
{// ����
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
{//���������������ʹ�������ֱ����cin����
	x.input(in);
	return in;
}
#endif // !chain_
