#ifndef heapNode_
#define heapNode_

using namespace std;

template <class T>
struct heapNode
{//堆节点在二叉树节点的基础上增加的父节点指针，便于向上遍历
	T element;//数据域
	heapNode<T> *leftChild, *rightChild, *parent;//指针域：左孩子、右孩子、父亲
	heapNode() { leftChild = rightChild = parent = NULL; }
	heapNode(const T& theElement) :element(theElement){
		leftChild = rightChild = parent = NULL;
	}
	heapNode(const T& theElement, heapNode *theLeftChild, heapNode *theRightChild, heapNode *theParent):element(theElement){
		leftChild = theLeftChild;
		rightChild = theRightChild;
		parent = theParent;
	}
};

#endif
