//��������ݽṹ����
#ifndef redBlackTree_
#define redBlackTree_

#include<iostream>
#include<queue>
#include"rbTreeNode.h"
#include"myExceptions.h"
using namespace std;
template <class K, class E>
class redBlackTree {
public:
	bool empty() const { return treeSize == 0; }//�����Ƿ�Ϊ����
	int size() const { return treeSize; }//�������Ĵ�С
	pair<const K, E>* find(const K& theKey) const;//���ҷ���
	void insert(const pair<const K, E>& thePair);//���뷽��
	void erase(const K& theKey);//ɾ������

	//redBlackTree() { root = NULL; treeSize = 0; };//���췽��

	redBlackTree() {
		//�����ó�ʼ��

		root = new rbTreeNode<pair<const K, E>>(pair<const K, E>(50, 'a'), BLACK);
		root->leftChild = new rbTreeNode<pair<const K, E>>(pair<const K, E>(10, 'b'), BLACK);
		root->leftChild->parent = root;
		root->rightChild = new rbTreeNode<pair<const K, E>>(pair<const K, E>(80, 'c'), BLACK);
		root->rightChild->parent = root;
		root->rightChild->rightChild = new rbTreeNode<pair<const K, E>>(pair<const K, E>(90, 'd'), RED);
		root->rightChild->rightChild->parent = root->rightChild;
	}

protected:
	rbTreeNode<pair<const K, E>> *root;//���ڵ�ָ��
	int treeSize;
	void leftRotate(rbTreeNode<pair<const K, E>>* node);//��������
	void rightRotate(rbTreeNode<pair<const K, E>>* node);//��������
};

template<class K, class E>
pair<const K, E>* redBlackTree<K, E>::find(const K& theKey) const {
	//��������ҷ�����
	//��������ҷ�������ͨ�����������Ĳ��ҷ�����ͬ
	//�Ӹ���ʼ������С�����󣬴������ҵ�˳����ң�ֱ���ҵ���ͬ�ؼ��ֻ򷵻ؿ�

	rbTreeNode<pair<const K, E> >* p = root;

	while (p != NULL) {
		if (theKey < p->element.first)
			p = p->leftChild;
		else if (theKey > p->element.first)
			p = p->rightChild;
		else
			return &p->element;
	}

	return NULL;
}

template<class K, class E>
void redBlackTree<K, E>::insert(const pair<const K, E>& thePair) {
	//��������뷽����

	//����ǰ��Ϊ������������ɫ���ڵ�
	if (root == NULL) {
		root = new rbTreeNode<pair<const K, E>>(thePair, BLACK);
		treeSize++;
		return;
	}

	//����ǰ����Ϊ���������Ȱ���һ���������ķ����ҵ�����λ��
	rbTreeNode<pair<const K, E> > *u = root, *pu = NULL, *gu = NULL;
	while (u != NULL) {
		pu = u;
		if (thePair.first < u->element.first)
			u = u->leftChild;
		else if (thePair.first > u->element.first)
			u = u->rightChild;
		else {
			//���ҵ����Ϲؼ���ʱ������Ԫ�ص�ֵ
			u->element.second = thePair.second;
			return;
		}
	}
	//���Ҳ���ƥ��ؼ���ʱ�������½ڵ㣬��ɫΪ��ɫ
	u = new rbTreeNode<pair<const K, E> >(thePair, RED);
	if (thePair.first < pu->element.first)
		pu->leftChild = u;
	else
		pu->rightChild = u;
	u->parent = pu;
	treeSize++;
	while (pu->color == RED) {
		//���ýڵ�ĸ��ڵ���ɫΪ��ɫ����������

		//������ڵ�ĸ��ڵ�Ϊ��ɫ�������ж��Ƿ�ΪXYr�Ͳ�ƽ��
		gu = pu->parent;
		if (gu->leftChild != NULL && gu->rightChild != NULL && gu->leftChild->color == RED && gu->rightChild->color == RED) {
			//��ΪXYr�Ͳ�ƽ��
			//��pu��gu���Һ����ɺ�ɫ��Ϊ��ɫ
			if (pu == gu->leftChild)
				gu->rightChild->color = BLACK;
			else
				gu->leftChild->color = BLACK;
			pu->color = BLACK;
			//���gu���Ǹ�����gu����ɫ�ɺ�ɫ��Ϊ��ɫ,����������
			if (gu != root)
				gu->color = RED;
			else
				return;
			u = gu;
			pu = u->parent;
		}
		else {
			//��ΪXYb�Ͳ�ƽ��
			if (pu == gu->leftChild) {
				if (u == pu->leftChild) {
					//1��LLb�Ͳ�ƽ��
					rightRotate(pu);
					pu->color = BLACK;
					gu->color = RED;
				}
				else {
					//2��LRb�Ͳ�ƽ��
					leftRotate(u);
					rightRotate(u);
					u->color = BLACK;
					gu->color = RED;
				}
			}
			else {
				if (u == pu->rightChild) {
					//3��RRb�Ͳ�ƽ��
					leftRotate(pu);
					pu->color = BLACK;
					gu->color = RED;
				}
				else {
					//4��RLb�Ͳ�ƽ��
					rightRotate(u);
					leftRotate(u);
					u->color = BLACK;
					gu->color = RED;
				}
			}
			break;
		}
	}
}

template<class K, class E>
void redBlackTree<K, E>::rightRotate(rbTreeNode<pair<const K, E>>* node) {
	//��node�ڵ���������ת��ɺ���Ϊ���ڵ�
	if (node->parent == NULL)
		throw illegalParameterValue("node can't be root");
	//pnodeΪҪ��ת�ڵ�ĸ��ڵ�,gnodeΪpnode�ĸ��ڵ�
	rbTreeNode<pair<const K, E>>* pnode = node->parent, *gnode = node->parent->parent;
	pnode->leftChild = node->rightChild;
	node->rightChild = pnode;
	if (pnode->parent == NULL) {
		node->parent = NULL;
		root = node;
	}
	else if (pnode == gnode->leftChild) {
		node->parent = gnode;
		gnode->leftChild = node;
	}
	else {
		node->parent = gnode;
		gnode->rightChild = node;
	}
	pnode->parent = node;
}

template<class K, class E>
void redBlackTree<K, E>::leftRotate(rbTreeNode<pair<const K, E>>* node) {
	//��node�ڵ���������ת��ɺ���Ϊ���ڵ�
	if (node->parent == NULL)
		throw illegalParameterValue("node can't be root");
	//pnodeΪҪ��ת�ڵ�ĸ��ڵ�,gnodeΪpnode�ĸ��ڵ�
	rbTreeNode<pair<const K, E>> *pnode = node->parent, *gnode = node->parent->parent;
	pnode->rightChild = node->leftChild;
	node->leftChild = pnode;
	if (pnode->parent == NULL) {
		node->parent = NULL;
		root = node;
	}
	else if (pnode == gnode->leftChild) {
		node->parent = gnode;
		gnode->leftChild = node;
	}
	else {
		node->parent = gnode;
		gnode->rightChild = node;
	}

	pnode->parent = node;
}
template<class K, class E>
void redBlackTree<K, E>::erase(const K& theKey) {
	//�����ɾ��������
	// ɾ���ؼ���ΪtheKey�Ľڵ�

	rbTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p���ڱ�������ppΪҪ��ǰ�����ڵ�ĸ��ڵ�
	while (p != NULL && p->element.first != theKey) {
		// ������
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
		return;
	//��ƥ��ؼ��֣�����

	//�ҵ�ƥ��ؼ��֣���Ϊ���������1������������2����һ������3����Ҷ�ڵ�
	//��ǰҪɾ���ڵ�Ϊp
	if (p->leftChild != NULL && p->rightChild != NULL) {
		// ���������ӵ����
		rbTreeNode<pair<const K, E> > *s = p->leftChild, *ps = p;
		while (s->rightChild != NULL) {
			// �ƶ��������������ڵ�
			ps = s;
			s = s->rightChild;
		}
		//sΪ�����������ڵ㣬psΪ���������ڵ�ĸ��ڵ�
		//�½��ڵ�q����q���뵽ɾ��λ��
		rbTreeNode<pair<const K, E> > *q = new rbTreeNode<pair<const K, E> >(s->element, p->leftChild, p->rightChild);
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
	rbTreeNode<pair<const K, E> > *c;
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
#endif