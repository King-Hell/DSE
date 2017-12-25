//������
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
	bool compare(linkedBinaryTree<E> &x) { return compare(root, x.root); }//�Ƚ�����������
protected:
	binaryTreeNode<E> *root;                // ���ڵ�
	int treeSize;                           // ����С
	static void(*visit)(binaryTreeNode<E>*);      // visit����
	static int count;         // ����ڵ���
	static void preOrder(binaryTreeNode<E> *t);
	static void inOrder(binaryTreeNode<E> *t);
	static void postOrder(binaryTreeNode<E> *t);
	static void countNodes(binaryTreeNode<E> *t)//����ڵ���
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
	static void addToCount(binaryTreeNode<E> *t)//ÿ����һ���ڵ�count��һ
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
{// ��������Ԫ��
	if (treeSize == 0)
		return NULL;
	else
		return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
	linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{//����������������������
	root = new binaryTreeNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;
	left.root = right.root = NULL;
	left.treeSize = right.treeSize = 0;
}
template<class E>
void linkedBinaryTree<E>::makeTreebyPre(E *preArray, E *inArray, int size) {
	//��ǰ��������������ɶ�����
	pre = preArray;//pre��in�����������Ա����
	in = inArray;
	orderSize = size;//orderSize��int�ͳ�Ա��������ʾǰ�����������ĳ���
	root=makeTreebyPre(0, size,0);//����ͬ�������ط���
	treeSize = size;
}
template<class E>
binaryTreeNode<E>* linkedBinaryTree<E>::makeTreebyPre(int left,int right,int pos) {
	//�ݹ�������������
	if (left >= right)
		return NULL;
	int i = left;//��ʼ��������������left��ʼѭ���Ƚϣ�ֱ���ҵ����ڵ������������λ��
	for (i; i < right; i++) {
		if (pre[pos]==in[i])
			break;
	}
	binaryTreeNode<E> *t = new binaryTreeNode<E>(in[i]);//�����¸��ڵ�
	t->leftChild = makeTreebyPre(left,i,pos+1);//�ݹ�����������
	t->rightChild = makeTreebyPre(i+1,right,pos+i-left+1);//�ݹ�����������
	return t;//���ظ��ڵ�
}
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree()
{//�Ƴ�������
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
{//�Ƴ�������
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
{// ǰ�����
	if (t != NULL)
	{
		linkedBinaryTree<E>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{//�������
	if (t != NULL)
	{
		inOrder(t->leftChild);
		linkedBinaryTree<E>::visit(t);
		inOrder(t->rightChild);
	}
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{// �������
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}

template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *))
{// ��α���
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
{// �������ĸ߶�
	if (t == NULL)
		return 0;
	int hl = height(t->leftChild);  // �������߶�
	int hr = height(t->rightChild); // �������߶�
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}
template <class E>
bool linkedBinaryTree<E>::compare(binaryTreeNode<E> *a, binaryTreeNode<E> *b) {//���رȽϷ������ݹ�Ƚ��������ڵ�
	if (a == NULL && b == NULL)//��ͬʱΪ��ʱ�����
		return true;
	if (a != NULL&&b == NULL || a == NULL&&b != NULL)//����һ����Ϊ��ʱ�������
		return false;
	if (a->element != b->element)
		return false;//���ڵ�Ԫ�ز����ʱ������false
	return compare(a->leftChild, b->leftChild) && compare(a->rightChild, b->rightChild);//�������������ȽϵĽ��
}
#endif
