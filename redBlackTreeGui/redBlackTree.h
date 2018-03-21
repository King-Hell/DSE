//红黑树数据结构定义
#ifndef redBlackTree_
#define redBlackTree_

#include<iostream>
#include"rbTreeNode.h"
#include"myExceptions.h"
using namespace std;
template <class K, class E>
class redBlackTree {
public:
	bool empty() const { return treeSize == 0; }//返回是否为空树
	int size() const { return treeSize; }//返回树的大小
	pair<const K, E>* find(const K& theKey) const;//查找方法
	void insert(const pair<const K, E>& thePair);//插入方法
	void erase(const K& theKey);//删除方法
	rbTreeNode<pair<const K, E>>* getRoot() { return root; };

	redBlackTree() { root = NULL; treeSize = 0; };//构造方法
	

protected:
	rbTreeNode<pair<const K, E>> *root;//根节点指针
	int treeSize;
	void leftRotate(rbTreeNode<pair<const K, E>>* node);//左旋方法
	void rightRotate(rbTreeNode<pair<const K, E>>* node);//右旋方法
	bool isBlack(rbTreeNode<pair<const K, E>>* node);//判断传入参数node是否为黑色节点，黑色返回true，红色返回false
};

template<class K, class E>
pair<const K, E>* redBlackTree<K, E>::find(const K& theKey) const {
	//红黑树查找方法：
	//红黑树查找方法与普通二叉搜索树的查找方法相同
	//从根开始，按照小于向左，大于向右的顺序查找，直到找到相同关键字或返回空

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
	//红黑树插入方法：

	//若当前树为空树，则插入黑色根节点
	if (root == NULL) {
		root = new rbTreeNode<pair<const K, E>>(thePair, BLACK);
		treeSize++;
		return;
	}

	//若当前树不为空树，则先按照一般搜索树的方法找到插入位置
	rbTreeNode<pair<const K, E> > *u = root, *pu = NULL, *gu = NULL;
	while (u != NULL) {
		pu = u;
		if (thePair.first < u->element.first)
			u = u->leftChild;
		else if (thePair.first > u->element.first)
			u = u->rightChild;
		else {
			//当找到符合关键字时，更新元素的值
			u->element.second = thePair.second;
			return;
		}
	}
	//当找不到匹配关键字时，建立新节点，颜色为红色
	u = new rbTreeNode<pair<const K, E> >(thePair, RED);
	if (thePair.first < pu->element.first)
		pu->leftChild = u;
	else
		pu->rightChild = u;
	u->parent = pu;
	treeSize++;
	while (pu->color == RED) {
		//若该节点的父节点颜色为黑色，则插入结束

		//若插入节点的父节点为红色，则先判断是否为XYr型不平衡
		gu = pu->parent;
		if (gu->leftChild != NULL && gu->rightChild != NULL && gu->leftChild->color == RED && gu->rightChild->color == RED) {
			//若为XYr型不平衡
			//将pu和gu的右孩子由红色改为黑色
			if (pu == gu->leftChild)
				gu->rightChild->color = BLACK;
			else
				gu->leftChild->color = BLACK;
			pu->color = BLACK;
			//如果gu不是根，将gu的颜色由黑色改为红色,否则插入结束
			if (gu != root)
				gu->color = RED;
			else
				return;
			u = gu;
			pu = u->parent;
		}
		else {
			//若为XYb型不平衡
			if (pu == gu->leftChild) {
				if (u == pu->leftChild) {
					//1、LLb型不平衡
					rightRotate(pu);
					pu->color = BLACK;
					gu->color = RED;
				}
				else {
					//2、LRb型不平衡
					leftRotate(u);
					rightRotate(u);
					u->color = BLACK;
					gu->color = RED;
				}
			}
			else {
				if (u == pu->rightChild) {
					//3、RRb型不平衡
					leftRotate(pu);
					pu->color = BLACK;
					gu->color = RED;
				}
				else {
					//4、RLb型不平衡
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
	//将node节点右旋，旋转完成后作为根节点
	if (node->parent == NULL)
		throw illegalParameterValue("node can't be root");
	//pnode为要旋转节点的父节点,gnode为pnode的父节点
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
	//将node节点左旋，旋转完成后作为根节点
	if (node->parent == NULL)
		throw illegalParameterValue("node can't be root");
	//pnode为要旋转节点的父节点,gnode为pnode的父节点
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
	//该方法判断node是否为黑色节点
	if (node == NULL || node->color == BLACK)
		return true;
	else
		return false;
}
template<class K, class E>
void redBlackTree<K, E>::erase(const K& theKey) {
	//红黑树删除方法：
	// 删除关键字为theKey的节点

	//先按照一般搜索树的删除方法
	//定位到要删除的节点位置
	rbTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p用于遍历树，pp为要当前遍历节点的父节点
	while (p != NULL && p->element.first != theKey) {
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)//无匹配关键字，返回
		return;

	//找到匹配关键字，分为三种情况：1、有两个孩子2、有一个孩子3、是叶节点
	//当前要删除节点为p
	if (p->leftChild != NULL && p->rightChild != NULL) {
		// 1、有两个孩子，将p的左子树的最大节点元素与其交换
		//令p为最大节点，最大节点仅有一棵子树或无子树，按照2、3情况处理
		rbTreeNode<pair<const K, E> > *s = p->leftChild, *ps = p;
		while (s->rightChild != NULL) {
			// 移动到左子树的最大节点
			ps = s;
			s = s->rightChild;
		}
		//s为左子树的最大节点，ps为左子树最大节点的父节点
		//新建节点y，将y插入到删除位置


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
		if (ps == p) //若左子树最大节点的父节点为p，则令pp为y                                                                                                                                                                   
			pp = q;
		else
			pp = ps;//若不是，则pp为其父节点 
		delete p;//释放要删除节点
		p = s;


	}
	//2、有一个孩子
	rbTreeNode<pair<const K, E> > *y;
	if (p->leftChild != NULL)
		y = p->leftChild;
	else
		y = p->rightChild;
	//c为要删除节点的左孩子或右孩子
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
	delete p;//释放该节点空间

	//红黑树的平衡修复：
	//y是替代被删除节点的节点
	//若被删除节点是黑色且y不是树根，需要进行平衡
	while (isBlack(y) && y != root) {
		rbTreeNode<pair<const K, E> > *py, *v, *w, *x;
		if (y != NULL)
			py = y->parent;
		else
			py = pp;
		bool pyc = py->color;//pyc为py节点在调整前的颜色
		if (y == py->rightChild) {
			//y是py的右节点，则v是py的左节点
			v = py->leftChild;
			if (isBlack(v)) {
				//Rb型不平衡

				if (isBlack(v->leftChild) && isBlack(v->rightChild)) {
					//1、Rb0不平衡
					v->color = RED;
					py->color = BLACK;
					//若py是根或py之前是红色，则平衡
					if (py == root || pyc == RED)
						return;
					//若py不是根且py之前是黑色，则可能需要重新调整
					y = py;
				}
				else if (isBlack(v->rightChild)) {
					//2、Rb1(i)型不平衡
					v->leftChild->color = BLACK;
					rightRotate(v);
					v->color = pyc;
					py->color = BLACK;
					return;
				}
				else {
					//3、Rb1(ii)和Rb2型不平衡
					w = v->rightChild;
					leftRotate(w);
					rightRotate(w);
					w->color = pyc;
					py->color = BLACK;
					return;
				}
			}
			else {
				//Rr型不平衡
				w = v->rightChild;
				if (isBlack(w->leftChild) && isBlack(w->rightChild)) {
					//4、Rr0型不平衡
					rightRotate(v);
					v->color = BLACK;
					w->color = RED;
				}
				else if (isBlack(w->rightChild)) {
					//5、Rr1(i)型不平衡
					w->leftChild->color = BLACK;
					leftRotate(w);
					rightRotate(w);
				}
				else {
					//6、Rr2(ii)和Rr2型不平衡
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
			//y是py的左节点,则v是py的右节点
			v = py->rightChild;
			if (isBlack(v)) {
				//Lb型不平衡

				if (isBlack(v->leftChild) && isBlack(v->rightChild)) {
					//1、Lb0不平衡
					v->color = RED;
					py->color = BLACK;
					//若py是根或py之前是红色，则平衡
					if (py == root || pyc == RED)
						return;
					//若py不是根且py之前是黑色，则可能需要重新调整
					y = py;
				}
				else if (isBlack(v->leftChild)) {
					//2、Lb1(i)型不平衡
					v->rightChild->color = BLACK;
					leftRotate(v);
					v->color = pyc;
					py->color = BLACK;
					return;
				}
				else {
					//3、Lb1(ii)和Lb2型不平衡
					w = v->leftChild;
					rightRotate(w);
					leftRotate(w);
					w->color = pyc;
					py->color = BLACK;
					return;
				}
			}
			else {
				//Lr型不平衡
				w = v->leftChild;
				if (isBlack(w->leftChild) && isBlack(w->rightChild)) {
					//4、Lr0型不平衡
					leftRotate(v);
					v->color = BLACK;
					w->color = RED;
				}
				else if (isBlack(w->leftChild)) {
					//5、Lr1(i)型不平衡
					w->rightChild->color = BLACK;
					rightRotate(w);
					leftRotate(w);
				}
				else {
					//6、Lr2(ii)和Lr2型不平衡
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