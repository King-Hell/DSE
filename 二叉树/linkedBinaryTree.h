//二叉树
#ifndef linkedBinaryTree_
#define linkedBinaryTree_

using namespace std;


#include <iostream>
#include "binaryTree.h"
#include "arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"


template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> >
{
public:
	linkedBinaryTree() { root = NULL; treeSize = 0; }
	~linkedBinaryTree() { erase(); };
	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	E* rootElement() const;
	void makeTree(const E& element, linkedBinaryTree<E>&, linkedBinaryTree<E>&);
	linkedBinaryTree<E>& removeLeftSubtree();
	linkedBinaryTree<E>& removeRightSubtree();
	void makeTreebyPre(E *pre, E *in, int size);
	
	void preOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; preOrder(root);
	}
	void inOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; inOrder(root);
	}
	void postOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; postOrder(root);
	}
	void levelOrder(void(*theVisit)(binaryTreeNode<E> *));
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrderOutput() { postOrder(output); cout << endl; }
	void levelOrderOutput() { levelOrder(output); cout << endl; }
	void erase()
	{
		postOrder(dispose);
		root = NULL;
		treeSize = 0;
	}
	int height() const { return height(root); }
	bool compare(linkedBinaryTree<E> &x) { return compare(root, x.root); }//比较两个二叉树
protected:
	binaryTreeNode<E> *root;                // 根节点
	int treeSize;                           // 树大小
	static void(*visit)(binaryTreeNode<E>*);      // visit方法
	static int count;         // 计算节点数
	static void preOrder(binaryTreeNode<E> *t);
	static void inOrder(binaryTreeNode<E> *t);
	static void postOrder(binaryTreeNode<E> *t);
	static void countNodes(binaryTreeNode<E> *t)//计算节点数
	{
		visit = addToCount;
		count = 0;
		preOrder(t);
	}
	static void dispose(binaryTreeNode<E> *t) { delete t; }
	static void output(binaryTreeNode<E> *t)
	{
		cout << t->element << ' ';
	}
	static void addToCount(binaryTreeNode<E> *t)//每遍历一个节点count加一
	{
		count++;
	}
	static int height(binaryTreeNode<E> *t);
	static bool compare(binaryTreeNode<E> *a, binaryTreeNode<E> *b);
	E *pre, *in;
	int orderSize;
	binaryTreeNode<E>* makeTreebyPre(int left, int right, int pos);
};
void(*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void(*linkedBinaryTree<char>::visit)(binaryTreeNode<char>*);
void(*linkedBinaryTree<pair<int, int> >::visit)(binaryTreeNode<pair<int, int> >*);
void(*linkedBinaryTree<pair<const int, char> >::visit)(binaryTreeNode<pair<const int, char> >*);
void(*linkedBinaryTree<pair<const int, int> >::visit)(binaryTreeNode<pair<const int, int> >*);

template<class E>
E* linkedBinaryTree<E>::rootElement() const
{// 返回树根元素
	if (treeSize == 0)
		return NULL;
	else
		return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
	linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{//由左子树和右子树生成树
	root = new binaryTreeNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;
	left.root = right.root = NULL;
	left.treeSize = right.treeSize = 0;
}
template<class E>
void linkedBinaryTree<E>::makeTreebyPre(E *preArray, E *inArray, int size) {
	//由前序和中序数组生成二叉树
	pre = preArray;//pre与in是两个数组成员变量
	in = inArray;
	orderSize = size;//orderSize是int型成员变量，表示前序和中序数组的长度
	root=makeTreebyPre(0, size,0);//调用同名的重载方法
	treeSize = size;
}
template<class E>
binaryTreeNode<E>* linkedBinaryTree<E>::makeTreebyPre(int left,int right,int pos) {
	//递归生成左右子树
	if (left >= right)
		return NULL;
	int i = left;//初始化计数变量，从left开始循环比较，直到找到根节点在中序数组的位置
	for (i; i < right; i++) {
		if (pre[pos]==in[i])
			break;
	}
	binaryTreeNode<E> *t = new binaryTreeNode<E>(in[i]);//创建新根节点
	t->leftChild = makeTreebyPre(left,i,pos+1);//递归生成左子树
	t->rightChild = makeTreebyPre(i+1,right,pos+i-left+1);//递归生成右子树
	return t;//返回根节点
}
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree()
{//移除左子树
	if (treeSize == 0)
		throw emptyTree();
	linkedBinaryTree<E> leftSubtree;
	leftSubtree.root = root->leftChild;
	count = 0;
	leftSubtree.treeSize = countNodes(leftSubtree.root);
	root->leftChild = NULL;
	treeSize -= leftSubtree.treeSize;

	return leftSubTree;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree()
{//移除右子树
	if (treeSize == 0)
		throw emptyTree();
	linkedBinaryTree<E> rightSubtree;
	rightSubtree.root = root->rightChild;
	count = 0;
	rightSubtree.treeSize = countNodes(rightSubtree.root);
	root->rightChild = NULL;
	treeSize -= rightSubtree.treeSize;

	return rightSubTree;
}

template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
{// 前序遍历
	if (t != NULL)
	{
		linkedBinaryTree<E>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{//中序遍历
	if (t != NULL)
	{
		inOrder(t->leftChild);
		linkedBinaryTree<E>::visit(t);
		inOrder(t->rightChild);
	}
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{// 后序遍历
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}

template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *))
{// 层次遍历
	arrayQueue<binaryTreeNode<E>*> q;
	binaryTreeNode<E> *t = root;
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

template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)
{// 返回树的高度
	if (t == NULL)
		return 0;
	int hl = height(t->leftChild);  // 左子树高度
	int hr = height(t->rightChild); // 右子树高度
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}
template <class E>
bool linkedBinaryTree<E>::compare(binaryTreeNode<E> *a, binaryTreeNode<E> *b) {//重载比较方法，递归比较两个根节点
	if (a == NULL && b == NULL)//当同时为空时，相等
		return true;
	if (a != NULL&&b == NULL || a == NULL&&b != NULL)//当有一个不为空时，不相等
		return false;
	if (a->element != b->element)
		return false;//当节点元素不相等时，返回false
	return compare(a->leftChild, b->leftChild) && compare(a->rightChild, b->rightChild);//返回左右子树比较的结果
}
#endif
