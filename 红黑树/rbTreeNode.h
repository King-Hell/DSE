#ifndef rbTreeNode_
#define rbTreeNode_

using namespace std;

template <class T>
struct rbTreeNode{
	T element;//������
	rbTreeNode<T> *leftChild,*rightChild;  // ָ����
	bool color;//��ɫ��0Ϊ��ɫ��1Ϊ��ɫ

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
