// 二叉搜索树
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
	bool empty() const { return treeSize == 0; }//返回是否为空
	int size() const { return treeSize; }//返回大小
	pair<const K, E>* find(const K& theKey) const;//搜索
	void insert(const pair<const K, E>& thePair);//插入
	void erase(const K& theKey);//删除

	void ascend() { inOrderOutput(); }//升序输出
};

template<class K, class E>
pair<const K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{//返回关键字为theKey的数对
	binaryTreeNode<pair<const K, E> > *p = root;
	while (p != NULL)
		// 从根节点开始依次遍历，小于根向左，大于向右
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			if (theKey > p->element.first)
				p = p->rightChild;
			else // 关键字相等时返回匹配数对
				return &p->element;

	// 若无匹配数对，返回空
	return NULL;
}

template<class K, class E>
void binarySearchTree<K, E>::insert(const pair<const K, E>& thePair)
{// 插入数对
	binaryTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p用于遍历树，pp用于储存当前
	while (p != NULL)
	{//从根节点开始遍历树
		pp = p;
		if (thePair.first < p->element.first)
			p = p->leftChild;
		else
			if (thePair.first > p->element.first)
				p = p->rightChild;
			else
			{//当找到符合关键字时，更新元素的值
				p->element.second = thePair.second;
				return;
			}
	}
	//当找不到匹配关键字时，建立新节点
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
{// 删除关键字为theKey的节点
	binaryTreeNode<pair<const K, E> > *p = root, *pp = NULL;//p用于遍历树，pp为要当前遍历节点的父节点
	while (p != NULL && p->element.first != theKey)
	{// 遍历树
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
		return; //无匹配关键字，返回

	//找到匹配关键字，分为三种情况：1、有两个孩子2、有一个孩子3、是叶节点
	//当前要删除节点为p
	if (p->leftChild != NULL && p->rightChild != NULL)
	{// 有两个孩子的情况
		binaryTreeNode<pair<const K, E> > *s = p->leftChild, *ps = p;
		while (s->rightChild != NULL)
		{// 移动到左子树的最大节点
			ps = s;
			s = s->rightChild;
		}
		//s为左子树的最大节点，ps为左子树最大节点的父节点
		//新建节点q，将q插入到删除位置
		binaryTreeNode<pair<const K, E> > *q = new binaryTreeNode<pair<const K, E> >(s->element, p->leftChild, p->rightChild);
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
	binaryTreeNode<pair<const K, E> > *c;
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

// 重载输出
template <class K, class E>
ostream& operator<<(ostream& out, const pair<K, E>& x)
{
	out << x.first << ' ' << x.second; return out;
}
#endif
