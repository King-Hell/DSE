//��������ݽṹ����
#ifndef redBlackTree_
#define redBlackTree_

#include<iostream>
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
	rbTreeNode<pair<const K, E>>* getRoot() { return root; };

	redBlackTree() { root = NULL; treeSize = 0; };//���췽��
	

protected:
	rbTreeNode<pair<const K, E>> *root;//���ڵ�ָ��
	int treeSize;
	void leftRotate(rbTreeNode<pair<const K, E>>* node);//��������
	void rightRotate(rbTreeNode<pair<const K, E>>* node);//��������
	bool isBlack(rbTreeNode<pair<const K, E>>* node);//�жϴ������node�Ƿ�Ϊ��ɫ�ڵ㣬��ɫ����true����ɫ����false
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
	if (pnode->leftChild != NULL)
		pnode->leftChild->parent = pnode;
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
	if (pnode->rightChild != NULL)
		pnode->rightChild->parent = pnode;
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
bool redBlackTree<K, E>::isBlack(rbTreeNode<pair<const K, E>>* node) {
	//�÷����ж�node�Ƿ�Ϊ��ɫ�ڵ�
	if (node == NULL || node->color == BLACK)
		return true;
	else
		return false;
}
template<class K, class E>
void redBlackTree<K, E>::erase(const K& theKey) {
	//�����ɾ��������
	// ɾ���ؼ���ΪtheKey�Ľڵ�

	//�Ȱ���һ����������ɾ������
	//��λ��Ҫɾ���Ľڵ�λ��
	rbTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p���ڱ�������ppΪҪ��ǰ�����ڵ�ĸ��ڵ�
	while (p != NULL && p->element.first != theKey) {
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)//��ƥ��ؼ��֣�����
		return;

	//�ҵ�ƥ��ؼ��֣���Ϊ���������1������������2����һ������3����Ҷ�ڵ�
	//��ǰҪɾ���ڵ�Ϊp
	if (p->leftChild != NULL && p->rightChild != NULL) {
		// 1�����������ӣ���p�������������ڵ�Ԫ�����佻��
		//��pΪ���ڵ㣬���ڵ����һ��������������������2��3�������
		rbTreeNode<pair<const K, E> > *s = p->leftChild, *ps = p;
		while (s->rightChild != NULL) {
			// �ƶ��������������ڵ�
			ps = s;
			s = s->rightChild;
		}
		//sΪ�����������ڵ㣬psΪ���������ڵ�ĸ��ڵ�
		//�½��ڵ�y����y���뵽ɾ��λ��


		rbTreeNode<pair<const K, E> > *q = new rbTreeNode<pair<const K, E> >(s->element, p->color);
		q->leftChild = p->leftChild, q->rightChild = p->rightChild;
		q->parent = p->parent;
		q->leftChild->parent = q, q->rightChild->parent = q;
		if (pp == NULL)
			root = q;
		else if (p == pp->leftChild)
			pp->leftChild = q;
		else
			pp->rightChild = q;
		if (ps == p) //�����������ڵ�ĸ��ڵ�Ϊp������ppΪy                                                                                                                                                                   
			pp = q;
		else
			pp = ps;//�����ǣ���ppΪ�丸�ڵ� 
		delete p;//�ͷ�Ҫɾ���ڵ�
		p = s;


	}
	//2����һ������
	rbTreeNode<pair<const K, E> > *y;
	if (p->leftChild != NULL)
		y = p->leftChild;
	else
		y = p->rightChild;
	//cΪҪɾ���ڵ�����ӻ��Һ���
	if (p == root)
		root = y;
	else {
		if (p == pp->leftChild)
			pp->leftChild = y;
		else pp->rightChild = y;
	}
	treeSize--;
	if (y != NULL && y != root)
		y->parent = pp;
	delete p;//�ͷŸýڵ�ռ�

	//�������ƽ���޸���
	//y�������ɾ���ڵ�Ľڵ�
	//����ɾ���ڵ��Ǻ�ɫ��y������������Ҫ����ƽ��
	while (isBlack(y) && y != root) {
		rbTreeNode<pair<const K, E> > *py, *v, *w, *x;
		if (y != NULL)
			py = y->parent;
		else
			py = pp;
		bool pyc = py->color;//pycΪpy�ڵ��ڵ���ǰ����ɫ
		if (y == py->rightChild) {
			//y��py���ҽڵ㣬��v��py����ڵ�
			v = py->leftChild;
			if (isBlack(v)) {
				//Rb�Ͳ�ƽ��

				if (isBlack(v->leftChild) && isBlack(v->rightChild)) {
					//1��Rb0��ƽ��
					v->color = RED;
					py->color = BLACK;
					//��py�Ǹ���py֮ǰ�Ǻ�ɫ����ƽ��
					if (py == root || pyc == RED)
						return;
					//��py���Ǹ���py֮ǰ�Ǻ�ɫ���������Ҫ���µ���
					y = py;
				}
				else if (isBlack(v->rightChild)) {
					//2��Rb1(i)�Ͳ�ƽ��
					v->leftChild->color = BLACK;
					rightRotate(v);
					v->color = pyc;
					py->color = BLACK;
					return;
				}
				else {
					//3��Rb1(ii)��Rb2�Ͳ�ƽ��
					w = v->rightChild;
					leftRotate(w);
					rightRotate(w);
					w->color = pyc;
					py->color = BLACK;
					return;
				}
			}
			else {
				//Rr�Ͳ�ƽ��
				w = v->rightChild;
				if (isBlack(w->leftChild) && isBlack(w->rightChild)) {
					//4��Rr0�Ͳ�ƽ��
					rightRotate(v);
					v->color = BLACK;
					w->color = RED;
				}
				else if (isBlack(w->rightChild)) {
					//5��Rr1(i)�Ͳ�ƽ��
					w->leftChild->color = BLACK;
					leftRotate(w);
					rightRotate(w);
				}
				else {
					//6��Rr2(ii)��Rr2�Ͳ�ƽ��
					x = w->rightChild;
					leftRotate(w);
					leftRotate(x);
					rightRotate(x);
					rightRotate(v);
					x->color = BLACK;
				}
				return;
			}
		}
		else {
			//y��py����ڵ�,��v��py���ҽڵ�
			v = py->rightChild;
			if (isBlack(v)) {
				//Lb�Ͳ�ƽ��

				if (isBlack(v->leftChild) && isBlack(v->rightChild)) {
					//1��Lb0��ƽ��
					v->color = RED;
					py->color = BLACK;
					//��py�Ǹ���py֮ǰ�Ǻ�ɫ����ƽ��
					if (py == root || pyc == RED)
						return;
					//��py���Ǹ���py֮ǰ�Ǻ�ɫ���������Ҫ���µ���
					y = py;
				}
				else if (isBlack(v->leftChild)) {
					//2��Lb1(i)�Ͳ�ƽ��
					v->rightChild->color = BLACK;
					leftRotate(v);
					v->color = pyc;
					py->color = BLACK;
					return;
				}
				else {
					//3��Lb1(ii)��Lb2�Ͳ�ƽ��
					w = v->leftChild;
					rightRotate(w);
					leftRotate(w);
					w->color = pyc;
					py->color = BLACK;
					return;
				}
			}
			else {
				//Lr�Ͳ�ƽ��
				w = v->leftChild;
				if (isBlack(w->leftChild) && isBlack(w->rightChild)) {
					//4��Lr0�Ͳ�ƽ��
					leftRotate(v);
					v->color = BLACK;
					w->color = RED;
				}
				else if (isBlack(w->leftChild)) {
					//5��Lr1(i)�Ͳ�ƽ��
					w->rightChild->color = BLACK;
					rightRotate(w);
					leftRotate(w);
				}
				else {
					//6��Lr2(ii)��Lr2�Ͳ�ƽ��
					x = w->leftChild;
					rightRotate(w);
					rightRotate(x);
					leftRotate(x);
					leftRotate(v);
					x->color = BLACK;
				}
				return;
			}
		}


	}






}
#endif