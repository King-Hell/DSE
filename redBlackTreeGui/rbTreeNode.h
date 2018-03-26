//������ڵ㶨��
#ifndef rbTreeNode_
#define rbTreeNode_

#define RED 0
#define BLACK 1

using namespace std;

template <class T>
struct rbTreeNode{
	T element;//������
	rbTreeNode<T> *leftChild,*rightChild;  // ���Һ���
	rbTreeNode<T> *parent;//����
	bool color;//��ɫ��0Ϊ��ɫ��1Ϊ��ɫ

	rbTreeNode() { 
		//�޲ι��췽��
		leftChild = rightChild = NULL; color = BLACK; 
		parent = NULL;
	}

	rbTreeNode(const T& theElement):element(theElement){
		//ָ�����ݹ��췽��
		leftChild = rightChild = NULL;
		parent = NULL;
	}

	rbTreeNode(const T& theElement, bool theColor, rbTreeNode<T>* theParent=NULL) :element(theElement) {
		//ָ�����ݡ���ɫ�븸�ڵ㹹�췽��
		leftChild = rightChild = NULL;
		color = theColor;
		parent = theParent;
	}

	void setLeftChild(rbTreeNode<T>* leftChild) {
		if (leftChild != NULL) {
			this->leftChild = leftChild;
			leftChild->parent = this;
		}
	}

	void setRightChild(rbTreeNode<T>* rightChild) {
		if (rightChild != NULL) {
			this->rightChild = rightChild;
			rightChild->parent = this;
		}
	}
};

#endif
