//红黑树数据结构定义
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
	bool empty() const { return treeSize == 0; }//返回是否为空树
	int size() const { return treeSize; }//返回树的大小
	pair<const K, E>* find(const K& theKey) const;//查找方法
	void insert(const pair<const K, E>& thePair);//插入方法
	void erase(const K& theKey);//删除方法

	//redBlackTree() { root = NULL; treeSize = 0; };//构造方法

	redBlackTree() {
		//测试用初始化

		root = new rbTreeNode<pair<const K, E>>(pair<const K, E>(50, 'a'), BLACK);
		root->leftChild = new rbTreeNode<pair<const K, E>>(pair<const K, E>(10, 'b'), BLACK);
		root->leftChild->parent = root;
		root->rightChild = new rbTreeNode<pair<const K, E>>(pair<const K, E>(80, 'c'), BLACK);
		root->rightChild->parent = root;
		root->rightChild->rightChild = new rbTreeNode<pair<const K, E>>(pair<const K, E>(90, 'd'), RED);
		root->rightChild->rightChild->parent = root->rightChild;
	}

protected:
	rbTreeNode<pair<const K, E>> *root;//根节点指针
	int treeSize;
	void leftRotate(rbTreeNode<pair<const K, E>>* node);//左旋方法
	void rightRotate(rbTreeNode<pair<const K, E>>* node);//右旋方法
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
	//红黑树删除方法：
	// 删除关键字为theKey的节点

	rbTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p用于遍历树，pp为要当前遍历节点的父节点
	while (p != NULL && p->element.first != theKey) {
		// 遍历树
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
		return;
	//无匹配关键字，返回

	//找到匹配关键字，分为三种情况：1、有两个孩子2、有一个孩子3、是叶节点
	//当前要删除节点为p
	if (p->leftChild != NULL && p->rightChild != NULL) {
		// 有两个孩子的情况
		rbTreeNode<pair<const K, E> > *s = p->leftChild, *ps = p;
		while (s->rightChild != NULL) {
			// 移动到左子树的最大节点
			ps = s;
			s = s->rightChild;
		}
		//s为左子树的最大节点，ps为左子树最大节点的父节点
		//新建节点q，将q插入到删除位置
		rbTreeNode<pair<const K, E> > *q = new rbTreeNode<pair<const K, E> >(s->element, p->leftChild, p->rightChild);
		if (pp == NULL)
			root = q;
		else if (p == pp->leftChild)
			pp->leftChild = q;
		else
			pp->rightChild = q;
		if (ps == p) //若左子树最大节点的父节点为p，则令pp为q
			pp = q;
		else
			pp = ps;//若不是，则pp为其父节点
		delete p;//释放要删除节点
		p = s;
	}
	//此时p最多有一个孩子
	rbTreeNode<pair<const K, E> > *c;
	if (p->leftChild != NULL)
		c = p->leftChild;
	else
		c = p->rightChild;
	//c为要删除节点的左孩子或右孩子
	if (p == root)
		root = c;
	else {
		if (p == pp->leftChild)
			pp->leftChild = c;
		else pp->rightChild = c;
	}
	treeSize--;
	delete p;//释放该节点空间
}
#endif