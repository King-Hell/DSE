#ifndef heapNode_
#define heapNode_

using namespace std;

template <class T>
struct heapNode
{//�ѽڵ��ڶ������ڵ�Ļ��������ӵĸ��ڵ�ָ�룬�������ϱ���
	T element;//������
	heapNode<T> *leftChild, *rightChild, *parent;//ָ�������ӡ��Һ��ӡ�����
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
