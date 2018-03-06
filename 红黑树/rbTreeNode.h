#ifndef rbTreeNode_
#define rbTreeNode_

using namespace std;

template <class T>
struct rbTreeNode{
	T element;//数据域
	rbTreeNode<T> *leftChild,*rightChild;  // 指针域
	bool color;//颜色，0为红色，1为黑色

	rbTreeNode() { leftChild = rightChild = NULL; }

	rbTreeNode(const T& theElement) :element(theElement){
		leftChild = rightChild = NULL;
	}

	rbTreeNode(const T& theElement,rbTreeNode *theLeftChild,rbTreeNode *theRightChild):element(theElement){
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

#endif
