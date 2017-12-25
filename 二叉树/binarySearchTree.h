// ����������
#ifndef binarySearchTree_
#define binarySearchTree_
#include "bsTree.h"
#include "linkedBinaryTree.h"
using namespace std;

template<class K, class E>
class binarySearchTree : public bsTree<K, E>,
	public linkedBinaryTree<pair<const K, E> >
{
public:
	bool empty() const { return treeSize == 0; }//�����Ƿ�Ϊ��
	int size() const { return treeSize; }//���ش�С
	pair<const K, E>* find(const K& theKey) const;//����
	void insert(const pair<const K, E>& thePair);//����
	void erase(const K& theKey);//ɾ��

	void ascend() { inOrderOutput(); }//�������
};

template<class K, class E>
pair<const K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{//���عؼ���ΪtheKey������
	binaryTreeNode<pair<const K, E> > *p = root;
	while (p != NULL)
		// �Ӹ��ڵ㿪ʼ���α�����С�ڸ����󣬴�������
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			if (theKey > p->element.first)
				p = p->rightChild;
			else // �ؼ������ʱ����ƥ������
				return &p->element;

	// ����ƥ�����ԣ����ؿ�
	return NULL;
}

template<class K, class E>
void binarySearchTree<K, E>::insert(const pair<const K, E>& thePair)
{// ��������
	binaryTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p���ڱ�������pp���ڴ��浱ǰ
	while (p != NULL)
	{//�Ӹ��ڵ㿪ʼ������
		pp = p;
		if (thePair.first < p->element.first)
			p = p->leftChild;
		else
			if (thePair.first > p->element.first)
				p = p->rightChild;
			else
			{//���ҵ����Ϲؼ���ʱ������Ԫ�ص�ֵ
				p->element.second = thePair.second;
				return;
			}
	}
	//���Ҳ���ƥ��ؼ���ʱ�������½ڵ�
	binaryTreeNode<pair<const K, E> > *newNode
		= new binaryTreeNode<pair<const K, E> >(thePair);
	if (root != NULL)
		if (thePair.first < pp->element.first)
			pp->leftChild = newNode;
		else
			pp->rightChild = newNode;
	else
		root = newNode;
	treeSize++;
}

template<class K, class E>
void binarySearchTree<K, E>::erase(const K& theKey)
{// ɾ���ؼ���ΪtheKey�Ľڵ�
	binaryTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p���ڱ�������ppΪҪ��ǰ�����ڵ�ĸ��ڵ�
	while (p != NULL && p->element.first != theKey)
	{// ������
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
		return; //��ƥ��ؼ��֣�����

	//�ҵ�ƥ��ؼ��֣���Ϊ���������1������������2����һ������3����Ҷ�ڵ�
	//��ǰҪɾ���ڵ�Ϊp
	if (p->leftChild != NULL && p->rightChild != NULL)
	{// ���������ӵ����
		binaryTreeNode<pair<const K, E> > *s = p->leftChild, *ps = p;
		while (s->rightChild != NULL)
		{// �ƶ��������������ڵ�
			ps = s;
			s = s->rightChild;
		}
		//sΪ�����������ڵ㣬psΪ���������ڵ�ĸ��ڵ�
		//�½��ڵ�q����q���뵽ɾ��λ��
		binaryTreeNode<pair<const K, E> > *q = new binaryTreeNode<pair<const K, E> >(s->element, p->leftChild, p->rightChild);
		if (pp == NULL)
			root = q;
		else if (p == pp->leftChild)
			pp->leftChild = q;
		else
			pp->rightChild = q;
		if (ps == p) //�����������ڵ�ĸ��ڵ�Ϊp������ppΪq
			pp = q;
		else
			pp = ps;//�����ǣ���ppΪ�丸�ڵ�
		delete p;//�ͷ�Ҫɾ���ڵ�
		p = s;
	}
	//��ʱp�����һ������
	binaryTreeNode<pair<const K, E> > *c;
	if (p->leftChild != NULL)
		c = p->leftChild;
	else
		c = p->rightChild;
	//cΪҪɾ���ڵ�����ӻ��Һ���
	if (p == root)
		root = c;
	else {
		if (p == pp->leftChild)
			pp->leftChild = c;
		else pp->rightChild = c;
	}
	treeSize--;
	delete p;//�ͷŸýڵ�ռ�
}

// �������
template <class K, class E>
ostream& operator<<(ostream& out, const pair<K, E>& x)
{
	out << x.first << ' ' << x.second; return out;
}
#endif
